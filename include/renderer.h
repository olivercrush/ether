#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "scene.h"
#include "camera.h"

void render(Scene* scene, Camera* camera, GLFWwindow* window);
