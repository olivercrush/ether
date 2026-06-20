#include "../include/mvp_matrix.h"
#include <stdlib.h>

mvp_matrix* mvp_matrix_make() {
    mvp_matrix* m = malloc(sizeof(mvp_matrix));
    if (m == NULL) {
        printf("Failed to create mvp_matrix");
        return NULL;
    }

    m->model_matrix = malloc(sizeof(mat4));
    if (m->model_matrix == NULL) {
        free(m);
        printf("Failed to create mvp_matrix");
        return NULL;
    }

    m->view_matrix = malloc(sizeof(mat4));
    if (m->view_matrix == NULL) {
        free(m);
        printf("Failed to create mvp_matrix");
        return NULL;
    }

    m->projection_matrix = malloc(sizeof(mat4));
    if (m->projection_matrix == NULL) {
        free(m);
        printf("Failed to create mvp_matrix");
        return NULL;
    }

    return m;
}

void mvp_matrix_delete(mvp_matrix *m) {
    if (m != NULL) {
        free(m->model_matrix);
        free(m->view_matrix);
        free(m->projection_matrix);

        if (m->computed_matrix != NULL)
            free(m->computed_matrix);

        free(m);
    }
}

void mvp_matrix_compute(mvp_matrix *m) {
    if (m->computed_matrix != NULL)
        free(m->computed_matrix);

    mat4 *c = malloc(sizeof(mat4));
    glm_mat4_mulN((mat4 *[]){m->projection_matrix, m->view_matrix, m->model_matrix}, 3, *c);
    m->computed_matrix = c;
}
