#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct Mesh {
    GLuint vertex_array;
    GLuint vertex_buffer;
    GLuint uv_buffer;
    size_t vertex_count;
} Mesh;

Mesh mesh_create(const GLfloat *v_data, size_t v_count, const GLfloat *u_data, size_t u_count);
void mesh_destroy(Mesh m);
