#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>
#include <cglm/cglm.h>
#include "init.h"
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
    
    GameObject objects[] = {
        game_object_cube_create(transform_1),
        game_object_cube_create(transform_2),
        game_object_cube_create(transform_3)
    };

    Scene* scene = scene_create(objects, sizeof(objects)/sizeof(objects[0]));
    Camera camera = camera_create((float) WIDTH / HEIGHT);

    do 
    {
        render(scene, &camera, window);
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    scene_destroy(scene);

	glfwTerminate();
    return 0;
}
