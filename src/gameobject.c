#include "../include/gameobject.h"
#include <stdlib.h>

GameObject game_object_create(Transform transform, Mesh* mesh, Material material) {
    GameObject o = { transform, mesh, material };
    return o;
}

GameObject game_object_cube_create(Transform transform, Mesh* mesh) {
    Material material = material_create("src/vertex.vertexshader", "src/fragment.fragmentshader", "src/uvtemplate.DDS");
    GameObject o = game_object_create(transform, mesh, material);
    return o;
}

void game_object_cleanup(GameObject* o) {
    if (o == NULL) return;
    //mesh_destroy(o->mesh);
    material_destroy(o->material);
}

void game_object_destroy(GameObject *o) {
    game_object_cleanup(o);
    free(o);
}
