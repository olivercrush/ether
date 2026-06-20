#include "../include/window.h"
#include <stdio.h>

static void set_window_hints() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* create_window(int width, int height) {
    set_window_hints();

    GLFWwindow* window;
    window = glfwCreateWindow(width, height, "Game Engine", NULL, NULL);
    if (window == NULL) {
        printf("Failed to open GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    return window;
}
