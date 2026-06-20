#include "../include/transform.h"
#include <cglm/affine.h>
#include <cglm/mat4.h>

void transform_to_mat4(Transform *t, vec4 *dest) {
    mat4 translation, scale, rotation;
    glm_translate_make(translation, t->position);
    glm_scale_make(scale, t->scale);
    glm_mat4_identity(rotation);
    glm_mat4_mulN((mat4 *[]) { &scale, &rotation, &translation }, 3, dest);
}
