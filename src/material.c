#include "material.h"
#include <stdlib.h>
#include <stdio.h>
#include "shader.h"
#include "dds.h"

Material* material_create(char *vertex_shader_path, char *fragment_shader_path, char *texture_path) {
Material* m = malloc(sizeof(Material));
 
    m->program_id = load_shader(vertex_shader_path, fragment_shader_path);
    if (m->program_id == 0) {
        printf("Failed to load shaders\n");
        return m;
    }

    m->texture_id = load_dds(texture_path);
    if (m->texture_id == 0) {
        printf("Failed to load texture\n");
        return m;
    }

    m->mvp_location = glGetUniformLocation(m->program_id, "MVP");
    if (m->mvp_location == -1) {
        printf("Failed to find mvp location\n");
        return m;
    }

    m->sampler_location = glGetUniformLocation(m->program_id, "myTextureSampler");
    if (m->sampler_location == -1) {
        printf("Failed to find sampler location\n");
        return m;
    }

    return m;
}

void material_bind(Material* m) {
    glUseProgram(m->program_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m->texture_id);
    glUniform1i(m->sampler_location, 0);
}

void material_destroy(Material* m) {
	glDeleteProgram(m->program_id);
	glDeleteTextures(1, &m->texture_id);
}
