#include <cglm/cglm.h>

typedef struct Transform {
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Transform;

void transform_to_mat4(Transform *t, mat4 dest);
