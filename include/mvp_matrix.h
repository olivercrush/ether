#include <cglm/cglm.h>
#include <stddef.h>

typedef struct mvp_matrix {
    mat4* model_matrix;
    mat4* view_matrix;
    mat4* projection_matrix;
    mat4* computed_matrix;
} mvp_matrix;

mvp_matrix* mvp_matrix_make();
void mvp_matrix_delete(mvp_matrix *m);
void mvp_matrix_compute(mvp_matrix *m);
