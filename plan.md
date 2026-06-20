# Refactor Plan — Functional Game Engine Structure

## Goal

Partition `main.c` into focused modules so multiple entities (e.g. cubes) can be
spawned independently, sharing GPU resources, with each instance carrying only its
own transform data. Follow a functional style: pure structs hold state, pure
functions transform them, nothing owns behavior.

---

## Layer breakdown

```
1. Engine init     -> GLFW, GLEW, OpenGL global state
2. Mesh            -> vertex/UV buffers uploaded to GPU (shared across instances)
3. Material        -> shader program + texture (shared across instances)
4. Transform       -> model matrix inputs, one per entity
5. Camera          -> view + projection matrix (shared)
6. Entity          -> mesh + material + transform, one per object in the scene
7. Scene           -> array of entities, update + render loop
```

---

## Target file structure

```
src/
  main.c
  mesh.c
  material.c
  camera.c
  entity.c
  scene.c
  window.c        <- exists
  mvp_matrix.c    <- to be absorbed into camera.c + transform.c
include/
  mesh.h
  material.h
  camera.h
  entity.h
  scene.h
  window.h        <- exists
  mvp_matrix.h    <- to be removed once absorbed
```

---

## Module specs

### mesh.h / mesh.c

Holds GPU geometry. One Mesh can be shared by many entities.

```c
typedef struct {
    GLuint vbo_vertices;
    GLuint vbo_uvs;
    int    vertex_count;
} Mesh;

Mesh* mesh_create(const GLfloat *verts, size_t vcount,
                  const GLfloat *uvs,   size_t ucount);
void  mesh_destroy(Mesh *m);
```

### material.h / material.c

Holds shader program and texture. Also shared across entities.

```c
typedef struct {
    GLuint program_id;
    GLuint texture_id;
    GLuint matrix_uniform;
    GLuint sampler_uniform;
} Material;

Material* material_create(const char *vert_path, const char *frag_path,
                           const char *texture_path);
void      material_destroy(Material *m);
```

### transform.h

Per-entity position, rotation, scale. Replaces raw model_matrix.

```c
typedef struct {
    vec3 position;
    vec3 rotation;  // euler angles in radians
    vec3 scale;
} Transform;

void transform_to_mat4(const Transform *t, mat4 dest);
```

No heap allocation — Transform is embedded by value inside Entity.

### camera.h / camera.c

Shared view + projection. Absorbs the view/projection parts of mvp_matrix.

```c
typedef struct {
    mat4 view;
    mat4 projection;
} Camera;

Camera* camera_create(float fov, float aspect, float near, float far,
                      vec3 eye, vec3 center, vec3 up);
void    camera_destroy(Camera *cam);
```

### entity.h / entity.c

Ties mesh + material + transform into one drawable unit.

```c
typedef struct {
    Mesh      *mesh;
    Material  *material;
    Transform  transform;
} Entity;

void entity_draw(const Entity *e, const Camera *cam);
```

`entity_draw` computes the MVP = projection * view * transform_to_mat4(), uploads
it as a uniform, binds the material, and issues the draw call.

### scene.h / scene.c

Owns an array of Entity pointers and drives the frame.

```c
void scene_render(Entity **entities, int count, const Camera *cam);
```

---

## What main.c becomes

```c
int main() {
    GLFWwindow *window = engine_init(WIDTH, HEIGHT);

    Mesh     *cube_mesh = mesh_create(g_vertex_buffer_data, 36,
                                      g_uv_buffer_data,     36);
    Material *mat       = material_create("src/vertex.vertexshader",
                                          "src/fragment.fragmentshader",
                                          "src/uvtemplate.DDS");
    Camera   *cam       = camera_create(45.0f, (float)WIDTH / HEIGHT,
                                        0.1f, 100.0f,
                                        (vec3){4,3,3}, (vec3){0,0,0}, (vec3){0,1,0});

    Entity cube_a = { cube_mesh, mat, { .position={0,0,0}, .scale={1,1,1} } };
    Entity cube_b = { cube_mesh, mat, { .position={3,0,0}, .scale={1,1,1} } };
    Entity *entities[] = { &cube_a, &cube_b };

    while (!glfwWindowShouldClose(window) &&
           glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene_render(entities, 2, cam);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    mesh_destroy(cube_mesh);
    material_destroy(mat);
    camera_destroy(cam);
    glfwTerminate();
    return 0;
}
```

---

## Functional principles to maintain

- No globals — Camera, Material, Mesh are passed explicitly to every function.
- Mesh is shared — multiple entities reference the same Mesh*, only Transform differs.
- entity_draw is pure — reads data, emits draw calls, does not mutate its inputs.
- transform_to_mat4 computes on the fly — no stale cache to manage.
- Cleanup mirrors creation — every *_create has a matching *_destroy.

---

## Implementation order

1. `transform.h` — no dependencies, no .c needed
2. `mesh.h` / `mesh.c` — depends on GL only
3. `camera.h` / `camera.c` — depends on cglm only
4. `material.h` / `material.c` — depends on existing shader.h + dds.h
5. `entity.h` / `entity.c` — depends on mesh, material, camera, transform
6. `scene.h` / `scene.c` — depends on entity, camera
7. Rewrite `main.c` using the above
8. Remove `mvp_matrix.h` / `mvp_matrix.c`
9. Update `CMakeLists.txt`
