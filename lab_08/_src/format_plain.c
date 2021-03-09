#include <limits.h>
#include <main.h>

struct Matrix *fread_plain_matrix(FILE *fd, enum MatrixMemoryType type) {
    struct Matrix *m;
    long rows = 0, cols = 0;
    long row, col, tmp;

    if (feof(fd))
        return 0;
    fscanf(fd, "%lu %lu", &rows, &cols);
    if (0 >= rows || 0 >= cols)
        return 0;
    m = matrix_create(rows, cols, type);
    for (row = 0; row < rows && !feof(fd); ++row) {
        for (col = 0; col < cols && !feof(fd); ++col) {
            fscanf(fd, "%ld", &tmp);
            matrix_put(m, row, col, tmp);
        }
    }
    return m;
}

void fwrite_plain_matrix(FILE *fd, struct Matrix *m) {
    if (0 != m && 0 != fd) {
        int row, col;

        fprintf(fd, "%llu %llu\n", m->rows, m->cols);
        for (row = 0; row < m->rows; ++row) {
            for (col = 0; col < m->cols; ++col) {
                fprintf(fd, "%d ", matrix_get(m, row, col));
            }
            fprintf(fd, "\n");
        }
    }
}
