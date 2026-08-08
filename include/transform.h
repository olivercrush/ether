#pragma once
#include <cglm/cglm.h>

typedef struct Transform {
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Transform;

void transform_to_model(Transform* t, mat4* dest);
