#ifndef BMAN_21_12_2020_MAIN_H
#define BMAN_21_12_2020_MAIN_H

#include <stdio.h>
#include <stdbool.h>

enum MatrixMemoryType {
    MATRIX_MEMORY_PLAIN,
    MATRIX_MEMORY_DATA_ROW,
    MATRIX_MEMORY_DATA_FLAT
};

enum MatrixFindDirect {
    FIND_LAST_ROW, FIND_FIRST_ROW,
    FIND_LAST_COL, FIND_FIRST_COL,
};

struct Matrix {
    enum MatrixMemoryType type;
    void  *data;
    size_t rows;
    size_t cols;
};

struct Matrix *matrix_create(int rows, int cols, enum MatrixMemoryType type);
struct Matrix *matrix_dup(struct Matrix *src);
void           matrix_destroy(struct Matrix **m);
void           matrix_copy(struct Matrix *dst, struct Matrix *src);
struct Matrix *matrix_mul(struct Matrix *a, struct Matrix *b);
struct Matrix *matrix_add(struct Matrix *a, struct Matrix *b);
void           matrix_delete_row(struct Matrix *m, int row);
void           matrix_delete_col(struct Matrix *m, int col);
int            matrix_get(struct Matrix *m, int row, int col);
void           matrix_put(struct Matrix *m, int row, int col, int val);
void           matrix_print(struct Matrix *m, FILE *out);
void           matrix_find_min(struct Matrix *m, enum MatrixFindDirect direct, int *row, int *col);
void           matrix_find_max(struct Matrix *m, enum MatrixFindDirect direct, int *row, int *col);

struct Matrix *fread_matrix(FILE *fd, enum MatrixMemoryType type);
void fwrite_matrix(FILE *fd, struct Matrix *m);

#endif //BMAN_21_12_2020_MAIN_H
