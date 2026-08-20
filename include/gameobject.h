#pragma once
#include "transform.h"
#include "material.h"
#include "mesh.h"

typedef struct GameObject {
    Transform transform;
    Mesh* mesh;
    Material* material;
} GameObject;

GameObject game_object_create(Transform transform, Mesh* mesh, Material* material);
void game_object_destroy(GameObject* o);
