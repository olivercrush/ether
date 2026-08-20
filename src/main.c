#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>
#include <cglm/cglm.h>
#include "init.h"
#include "mesh.h"
#include "renderer.h"
#include "transform.h"
#include "scene.h"
#include "gameobject.h"

const int WIDTH = 1024;
const int HEIGHT = 768;

int main() {
    GLFWwindow* window = init_engine(WIDTH, HEIGHT);
    if (window == NULL) {
        printf("Error while trying to init engine");
        return -1;
    }

    Transform transform_1 = {{ 1.0f, -2.0f, 2.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 3.0f, 1.0f }};
    Transform transform_2 = {{ -5.0f, 0.0f, 2.0f }, { 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }};
    Transform transform_3 = {{ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 2.0f }};
    Transform transform_4 = {{ 5.0f, 3.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }};

    Mesh* mesh = mesh_cube_create();
    GameObject objects[] = {
        game_object_cube_create(transform_1, mesh),
        game_object_cube_create(transform_2, mesh),
        game_object_cube_create(transform_3, mesh),
        game_object_cube_create(transform_4, mesh)
    };

    Scene* scene = scene_create(objects, sizeof(objects)/sizeof(objects[0]));
    Camera camera = camera_create(window, WIDTH, HEIGHT);

    double last_time = glfwGetTime();
    do
    {
        double current_time = glfwGetTime();
        float delta_time = (float) current_time - last_time;
        last_time = current_time;

        render(scene, &camera, window, delta_time);
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    scene_destroy(scene);
    mesh_destroy(mesh);

	glfwTerminate();
    return 0;
}
