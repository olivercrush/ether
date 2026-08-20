#pragma once
#include "transform.h"
#include "material.h"
#include "mesh.h"

typedef struct GameObject {
    Transform transform;
    Mesh* mesh;
    Material material;
} GameObject;

GameObject game_object_create(Transform transform, Mesh* mesh, Material material);
GameObject game_object_cube_create(Transform transform, Mesh* mesh);
void game_object_cleanup(GameObject* o);
void game_object_destroy(GameObject* o);
