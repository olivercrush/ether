#pragma once
#include "gameobject.h"

typedef struct Scene {
    GameObject* objects;
    int count;
} Scene;

Scene* scene_create(GameObject* objects, int count);
void scene_destroy(Scene* scene);
void scene_render(Scene* scene);
