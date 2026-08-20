#include "../include/gameobject.h"
#include <stdlib.h>

GameObject game_object_create(Transform transform, Mesh* mesh, Material* material) {
    GameObject o = { transform, mesh, material };
    return o;
}

void game_object_destroy(GameObject *o) {
    free(o);
}
