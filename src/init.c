#include "../include/init.h"
#include <stdio.h>

GLFWwindow* init_engine(int width, int height) {
    glewExperimental = true;
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return NULL;
    }

    GLFWwindow* window = create_window(width, height);

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return NULL;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    return window;
}
