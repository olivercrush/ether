#pragma once
#include <cglm/cglm.h>

typedef struct Camera {
    mat4 view;
    mat4 projection;
} Camera;

Camera camera_create(float aspect);
