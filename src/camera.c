#include "camera.h"
#include <GLFW/glfw3.h>
#include <cglm/cam.h>
#include <cglm/vec3.h>

Camera camera_create(GLFWwindow* window, int screen_width, int screen_height) {
    Camera camera = {
        .position = { 0.0f, 0.0f, 5.0f },
        .horizontal_angle = 3.14f,
        .vertical_angle = 0.0f,
        .initialFov = 60.0f,
        .speed = 3.0f,
        .mouse_speed = 0.005f,
        .screen_width = screen_width,
        .screen_height = screen_height
    };

    camera_compute_from_inputs(&camera, window, 0.0f);

    return camera;
}

void camera_compute_from_inputs(Camera *camera, GLFWwindow* window, float delta_time) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, (float) camera->screen_width/2, (float) camera->screen_height/2);

    camera->horizontal_angle += camera->mouse_speed * delta_time * ((float) camera->screen_width/2 - xpos);
    camera->vertical_angle += camera->mouse_speed * delta_time * ((float) camera->screen_height/2 - ypos);

    vec3 direction = { 
        cos(camera->vertical_angle) * sin(camera->horizontal_angle),
        sin(camera->vertical_angle),
        cos(camera->vertical_angle) * cos(camera->horizontal_angle),
    };

    vec3 right = {
        sin(camera->horizontal_angle - 3.14f/2.0f),
        0,
        cos(camera->horizontal_angle - 3.14f/2.0f)
    };

    vec3 up;
    glm_vec3_cross(right, direction, up);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glm_vec3_muladds(direction, delta_time * camera->speed, camera->position);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glm_vec3_muladds(direction, -delta_time * camera->speed, camera->position);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        glm_vec3_muladds(right, delta_time * camera->speed, camera->position);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glm_vec3_muladds(right, -delta_time * camera->speed, camera->position);

    vec3 target;
    glm_vec3_add(camera->position, direction, target);
    glm_lookat(camera->position, target, up, camera->view);

    glm_perspective(glm_rad(camera->initialFov), (float) camera->screen_width / camera->screen_height, 0.1f, 100.0f, camera->projection);
}
