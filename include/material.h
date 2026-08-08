#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct Material {
    GLuint program_id;
    GLuint texture_id;
    GLint mvp_location;
    GLint sampler_location;
} Material;

Material material_create(char vertex_shader_path[], char fragment_shader_path[], char texture_path[]);
void material_bind(Material m);
void material_destroy(Material m);
