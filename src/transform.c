#include "../include/transform.h"
#include <cglm/affine.h>
#include <cglm/mat4.h>

void transform_to_model(Transform* t, mat4* dest) {
    mat4 translation, scale, rotation;
    glm_translate_make(translation, t->position);
    glm_scale_make(scale, t->scale);
    glm_mat4_identity(rotation); // Ignoring for now, expected
    glm_mat4_mulN((mat4 *[]) { &translation, &rotation, &scale }, 3, *dest);
}
