#include "../include/init.h"
#include <GLFW/glfw3.h>
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    return window;
}
