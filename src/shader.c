#include "../include/shader.h"

#include <stdio.h>
#include <stdlib.h>

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "Cannot open shader file: %s\n", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);
    char *buf = malloc(len + 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);
    return buf;
}

static GLuint compile_shader(GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
        char *log = malloc(log_len);
        glGetShaderInfoLog(shader, log_len, NULL, log);
        fprintf(stderr, "Shader compile error:\n%s\n", log);
        free(log);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint load_shader(const char *vertex_path, const char *fragment_path) {
    char *vert_src = read_file(vertex_path);
    char *frag_src = read_file(fragment_path);
    if (!vert_src || !frag_src) {
        free(vert_src);
        free(frag_src);
        return 0;
    }

    GLuint vert = compile_shader(GL_VERTEX_SHADER, vert_src);
    GLuint frag = compile_shader(GL_FRAGMENT_SHADER, frag_src);
    free(vert_src);
    free(frag_src);

    if (!vert || !frag) {
        glDeleteShader(vert);
        glDeleteShader(frag);
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    glDeleteShader(vert);
    glDeleteShader(frag);

    GLint ok;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
        char *log = malloc(log_len);
        glGetProgramInfoLog(program, log_len, NULL, log);
        fprintf(stderr, "Shader link error:\n%s\n", log);
        free(log);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}
