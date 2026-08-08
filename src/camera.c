#include "camera.h"
#include <cglm/cam.h>

Camera camera_create(float aspect) {
    Camera camera = {0};
    glm_lookat((vec3) {5, 5, 0}, (vec3) {0, 0, 0}, (vec3) {0, 1, 0}, camera.view);
    glm_perspective(glm_rad(60.0f), aspect, 0.1f, 100.0f, camera.projection);
    return camera;
}
