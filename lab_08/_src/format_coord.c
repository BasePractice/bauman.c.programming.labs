#include <main.h>

struct Matrix *fread_coord_matrix(FILE *fd, enum MatrixMemoryType type) {
    struct Matrix *m;
    size_t rows = 0, cols = 0;
    int i = 0, row = 0, col = 0, all = 0, val = 0;

    if (feof(fd))
        return 0;
    fscanf(fd, "%lu %lu %lu", &rows, &cols, &all);
    if (0 >= rows || 0 >= cols)
        return 0;
    m = matrix_create(rows, cols, type);
    for (i = 0; i < all && !feof(fd); ++i) {
        fscanf(fd, "%lu %lu %lu", &row, &col, &val);
        matrix_put(m, row - 1, col - 1, val);
    }
    return m;
}

void fwrite_coord_matrix(FILE *fd, struct Matrix *m) {
    if (0 != fd && 0 != m) {
        size_t all = 0;
        int row = 0, col = 0;

        /** Не оптимально, но зато быстро в реализации */
        for (row = 0; row < m->rows; ++row) {
            for (col = 0; col < m->cols; ++col) {
                int v = matrix_get(m, row, col);
                if (0 != v) {
                    ++all;
                }
            }
        }
        fprintf(fd, "%lu %lu %lu\n", m->rows, m->cols, all);
        for (row = 0; row < m->rows; ++row) {
            for (col = 0; col < m->cols; ++col) {
                int v = matrix_get(m, row, col);
                if (0 != v) {
                    fprintf(fd, "%lu %lu %lu\n", row + 1, col + 1, v);
                }
            }
        }
    }
}
