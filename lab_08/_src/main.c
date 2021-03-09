#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h>
#include <main.h>

struct Matrix *matrix_dup(struct Matrix *src) {
    struct Matrix *copy = matrix_create(src->rows, src->cols, src->type);
    matrix_copy(copy, src);
    return copy;
}

void matrix_copy(struct Matrix *dst, struct Matrix *src) {
    if (dst->rows >= src->rows && dst->cols >= src->cols) {
        int row, col;

        for (row = 0; row < src->rows; ++row) {
            for (col = 0; col < src->cols; ++col) {
                matrix_put(dst, row, col, matrix_get(src, row, col));
            }
        }
    }
}

void matrix_delete_row(struct Matrix *m, int row) {
    if (0 != m && 0 != m->data && m->rows > row) {
        struct Matrix *n = matrix_create(m->rows - 1, m->cols, m->type);
        int row_c, row_i, col_c;

        for (row_c = 0, row_i = 0; row_c < m->rows; ++row_c) {
            if (row_c == row)
                continue;
            for (col_c = 0; col_c < m->cols; ++col_c) {
                matrix_put(n, row_i, col_c, matrix_get(m, row_c, col_c));
            }
            ++row_i;
        }
        matrix_destroy(&m);
        m = calloc(1, sizeof(struct Matrix));
        m->data = n->data;
        m->rows = n->rows;
        m->cols = n->cols;
        m->type = n->type;
    }
}

void matrix_delete_col(struct Matrix *m, int col) {
    if (0 != m && 0 != m->data && m->cols > col) {
        struct Matrix *n = matrix_create(m->rows, m->cols - 1, m->type);
        int row_c, col_i, col_c;

        for (row_c = 0; row_c < m->rows; ++row_c) {
            for (col_c = 0, col_i = 0; col_c < m->cols; ++col_c) {
                if (col == col_c)
                    continue;
                matrix_put(n, row_c, col_i, matrix_get(m, row_c, col_c));
                ++col_i;
            }
        }
        matrix_destroy(&m);
        m = calloc(1, sizeof(struct Matrix));
        m->data = n->data;
        m->rows = n->rows;
        m->cols = n->cols;
        m->type = n->type;
    }
}

struct Matrix *matrix_create(int rows, int cols, enum MatrixMemoryType type) {
    struct Matrix *m = calloc(1, sizeof(struct Matrix));
    m->cols = cols;
    m->rows = rows;
    m->type = type;

    switch (type) {
        case MATRIX_MEMORY_DATA_ROW: {
            fprintf(stderr, "MATRIX_MEMORY_DATA_ROW type not implement yet\n");
            break;
        }
        case MATRIX_MEMORY_DATA_FLAT: {
            m->data = calloc(rows * cols, sizeof(int));
            memset(m->data, 0, rows * cols * sizeof(int));
            break;
        }
        case MATRIX_MEMORY_PLAIN:
        default: {
            int i;

            m->data = (int **) calloc(rows, sizeof(int *));
            for (i = 0; i < rows; ++i) {
                int **p_data = (int **) m->data;
                p_data[i] = (int *) calloc(cols, sizeof(int));
                memset(p_data[i], 0, cols * sizeof(int));
            }
            break;
        }
    }
    return m;
}

struct Matrix *matrix_add(struct Matrix *a, struct Matrix *b) {
    struct Matrix *m = 0;
    if (a->cols == b->cols && a->rows == b->rows) {
        int row, col;

        m = matrix_create(a->rows, a->cols, a->type);
        for (row = 0; row < a->rows; ++row) {
            for (col = 0; col < a->cols; ++col) {
                matrix_put(m, row, col, matrix_get(a, row, col) + matrix_get(b, row, col));
            }
        }
    }
    return m;
}

struct Matrix *matrix_mul(struct Matrix *a, struct Matrix *b) {
    struct Matrix *m = 0;
    if (a->cols == b->cols && a->rows == b->rows) {
        int row, col;

        m = matrix_create(a->rows, a->cols, a->type);
        for (row = 0; row < a->rows; ++row) {
            for (col = 0; col < a->cols; ++col) {
                int k;

                matrix_put(m, row, col, 0);
                for (k = 0; k < a->cols; ++k) {
                    int v = matrix_get(m, row, col);
                    v += matrix_get(a, row, k) * matrix_get(b, k, col);
                    matrix_put(m, row, col, v);
                }
            }
        }
    }
    return m;
}

void matrix_destroy(struct Matrix **m) {
    if (0 != m && 0 != *m) {
        struct Matrix *p = *m;

        if (0 == p->data) {
            free(p);
            *m = 0;
            return;
        }

        switch (p->type) {
            case MATRIX_MEMORY_DATA_ROW: {
                fprintf(stderr, "MATRIX_MEMORY_DATA_ROW type not implement yet\n");
                break;
            }
            case MATRIX_MEMORY_DATA_FLAT: {
                free(p->data);
                break;
            }
            case MATRIX_MEMORY_PLAIN:
            default: {
                int i;
                int **p_data = (int **) p->data;

                for (i = 0; i < p->rows; ++i) {
                    free(p_data[i]);
                }
                free(p_data);
                break;
            }
        }
        free(p);
        *m = 0;
    }
}

int matrix_get(struct Matrix *m, int row, int col) {
    if (0 != m && 0 != m->data) {
        switch (m->type) {
            case MATRIX_MEMORY_DATA_ROW: {
                fprintf(stderr, "MATRIX_MEMORY_DATA_ROW type not implement yet\n");
                break;
            }
            case MATRIX_MEMORY_DATA_FLAT: {
                int *p_data = (int *) m->data;

                if (row < m->rows && col < m->cols)
                    return p_data[row * col];
                break;
            }
            case MATRIX_MEMORY_PLAIN:
            default: {
                int **p_data = (int **) m->data;

                if (row < m->rows && col < m->cols)
                    return p_data[row][col];
                break;
            }
        }
    }
    return 0;
}

void matrix_put(struct Matrix *m, int row, int col, int val) {
    if (0 != m && 0 != m->data) {
        switch (m->type) {
            case MATRIX_MEMORY_DATA_ROW: {
                break;
            }
            case MATRIX_MEMORY_DATA_FLAT: {
                int *p_data = (int *) m->data;

                if (row < m->rows && col < m->cols)
                    p_data[row * col] = val;
                break;
            }
            case MATRIX_MEMORY_PLAIN:
            default: {
                int **p_data = (int **) m->data;

                if (row < m->rows && col < m->cols)
                    p_data[row][col] = val;
                break;
            }
        }
    }
}

void matrix_print(struct Matrix *m, FILE *out) {
    if (0 != m && 0 != m->data && 0 != out) {
        int i, k;

        for (i = 0; i < m->rows; ++i) {
            for (k = 0; k < m->cols; ++k) {
                fprintf(out, "%3d ", matrix_get(m, i, k));
            }
            fprintf(out, "\n");
        }
    }
}

/** matrix_min и matrix_max можно свести к одной функции */
static int matrix_min(struct Matrix *m) {
    if (0 != m && 0 != m->data) {
        int row, col, min = matrix_get(m, 0, 0);
        for (row = 0; row < m->rows; row++) {
            for (col = 0; col < m->cols; col++) {
                int v = matrix_get(m, row, col);
                if (v < min) {
                    min = v;
                }
            }
        }
        return min;
    }
    return INT_MIN;
}

static int matrix_max(struct Matrix *m) {
    if (0 != m && 0 != m->data) {
        int row, col, max = matrix_get(m, 0, 0);
        for (row = 0; row < m->rows; row++) {
            for (col = 0; col < m->cols; col++) {
                int v = matrix_get(m, row, col);
                if (v > max) {
                    max = v;
                }
            }
        }
        return max;
    }
    return INT_MIN;
}

/** matrix_find_min и matrix_find_max можно свести к одной функции */
void matrix_find_min(struct Matrix *m, enum MatrixFindDirect direct, int *row, int *col) {
    *row = 0;
    *col = 0;
    if (0 != m && 0 != m->data) {
        int min = matrix_min(m), i, k;
        if (direct == FIND_FIRST_ROW || direct == FIND_LAST_ROW) {
            for (i = 0; i < m->rows; i++) {
                for (k = 0; k < m->cols; k++) {
                    int v = matrix_get(m, i, k);
                    if (v == min) {
                        *row = i;
                        *col = k;
                        if (FIND_FIRST_ROW == direct)
                            return;
                    }
                }
            }
        } else {
            for (k = 0; k < m->cols; k++) {
                for (i = 0; i < m->rows; i++) {
                    int v = matrix_get(m, i, k);
                    if (v == min) {
                        *row = i;
                        *col = k;
                        if (FIND_FIRST_COL == direct)
                            return;
                    }
                }
            }
        }
    }
}

void matrix_find_max(struct Matrix *m, enum MatrixFindDirect direct, int *row, int *col) {
    *row = 0;
    *col = 0;
    if (0 != m && 0 != m->data) {
        int max = matrix_max(m), i, k;
        if (direct == FIND_FIRST_ROW || direct == FIND_LAST_ROW) {
            for (i = 0; i < m->rows; i++) {
                for (k = 0; k < m->cols; k++) {
                    int v = matrix_get(m, i, k);
                    if (v == max) {
                        *row = i;
                        *col = k;
                        if (FIND_FIRST_ROW == direct)
                            return;
                    }
                }
            }
        } else {
            for (k = 0; k < m->cols; k++) {
                for (i = 0; i < m->rows; i++) {
                    int v = matrix_get(m, i, k);
                    if (v == max) {
                        *row = i;
                        *col = k;
                        if (FIND_FIRST_COL == direct)
                            return;
                    }
                }
            }
        }
    }
}

