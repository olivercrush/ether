#pragma once
#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

typedef struct Camera {
    vec3 position;
    float horizontal_angle;
    float vertical_angle;
    float initialFov;
    float speed;
    float mouse_speed;
    int screen_width;
    int screen_height;
    mat4 view;
    mat4 projection;
} Camera;

Camera camera_create(GLFWwindow* window, int screen_width, int screen_height);
void camera_compute_from_inputs(Camera *camera, GLFWwindow* window, float delta_time);
