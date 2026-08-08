#include "renderer.h"
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include "transform.h"
#include "material.h"

void render(Scene *scene, Camera *camera, GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < scene->count; i++) {
        material_bind(scene->objects[i].material);

        mat4 model, mvp;
        transform_to_model(&scene->objects[i].transform, &model);
        glm_mat4_mulN((mat4* []){ &camera->projection, &camera->view, &model }, 3, mvp);

        glUniformMatrix4fv(scene->objects[i].material.mvp_location, 1, GL_FALSE, *mvp);
        glBindVertexArray(scene->objects[i].mesh.vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, scene->objects[i].mesh.vertex_count);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}
