#include "../include/mesh.h"
#include <GL/glext.h>
#include <stdlib.h>

Mesh mesh_create(const GLfloat *v_data, size_t v_count, const GLfloat *u_data, size_t u_count) {
    Mesh mesh = {0};
    mesh.vertex_count = v_count / 3;

    glGenVertexArrays(1, &mesh.vertex_array);
    glBindVertexArray(mesh.vertex_array);

    glGenBuffers(1, &mesh.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), v_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &mesh.uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, u_count * sizeof(GLfloat), u_data, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    return mesh;
}

void mesh_destroy(Mesh m) {
    glDeleteBuffers(1, &m.vertex_buffer);
    glDeleteBuffers(1, &m.uv_buffer);
	glDeleteVertexArrays(1, &m.vertex_array);
}
