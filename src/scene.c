#include "scene.h"
#include "gameobject.h"
#include <stdlib.h>
#include <string.h>

Scene* scene_create(GameObject* objects, int count) {
    Scene *s = malloc(sizeof(Scene));
    if (s == NULL) return NULL;

    s->objects = malloc(count * sizeof(GameObject));
    if (s->objects == NULL) {
        free(s);
        return NULL;
    }

    memcpy(s->objects, objects, count * sizeof(GameObject));
    s->count = count;
    return s;
}

void scene_destroy(Scene *s) {
    if (s == NULL) return;

    for (int i = 0; i < s->count; i++)
        game_object_destroy(&s->objects[i]);

    free(s->objects);
    free(s);
}

void scene_render(Scene *scene) {
    // NOTHING YET, WORKING ON SETUP FIRST
}
