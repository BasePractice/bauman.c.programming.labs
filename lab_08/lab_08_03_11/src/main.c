#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <main.h>

struct Matrix *read_matrix(char *filename) {
    struct Matrix *m = 0;
    FILE *fd = fopen(filename, "r");
    if (0 != fd) {
        m = fread_matrix(fd, MATRIX_MEMORY_PLAIN);
        fclose(fd);
    }
    return m;
}

struct Matrix *operate(char *op, char *file1, char *file2) {
    struct Matrix *mtr_1 = read_matrix(file1);
    struct Matrix *mtr_2 = read_matrix(file2);
    struct Matrix *result = 0;

    if (0 == strcmp("a", op)) {
        result = matrix_mul(mtr_1, mtr_2);
    } else if (0 == strcmp("m", op)) {
        result = matrix_add(mtr_1, mtr_2);
    }

    matrix_destroy(&mtr_1);
    matrix_destroy(&mtr_2);
    return result;
}

static int det(struct Matrix *x, int n, int t) {
    int i, j, k, m, l, s, b = 0;
    struct Matrix *d = matrix_create(x->rows, x->cols, x->type);
    if (n < 3) {
        return ((matrix_get(x, 0, 0) * matrix_get(x, 1, 1)) - (matrix_get(x, 0, 1) * matrix_get(x, 1, 0)));
    } else {
        k = 0;
        l = 0;
        for (i = 0; i < n; i++) {
            m = 0;
            for (j = 0; j < n; j++) {
                if (!((i == k) || (j == t))) {
                    matrix_put(d, l, m, matrix_get(x, i, j));
                    m++;
                }
            }
            if (i != k) l++;
        }
        for (s = 0; s < n - 1; s++) {
            b += matrix_get(x, k, s) * (int) pow(-1, ((k + 1) + (s + 1))) * det(d, n - 1, s);
        }
    }
    return b;
}

#if defined(ENTRY_POINT)

int main(int argc, char **argv) {
    struct Matrix *m = 0;
    int arg_i;
    if (argc < 4) {
        fprintf(stderr, "Usage: %s action mtr_1.txt [mtr_2.txt] res.txt\n", argv[0]);
    }
    if (0 == strcmp("o", argv[1])) {
        struct Matrix *ret = matrix_create(1, 1, MATRIX_MEMORY_PLAIN);
        m = read_matrix(argv[2]);
        matrix_put(ret, 0, 0, det(m, 0, 0));
        matrix_destroy(&m);
        m = ret;
        arg_i = 3;
    } else {
        arg_i = 4;
        m = operate(argv[1], argv[2], argv[3]);
    }
    if (0 != m) {
        FILE *out = fopen(argv[arg_i], "w+");
        if (0 != out && 0 != m) {
            fwrite_matrix(out, m);
            fclose(out);
        }
    }
    matrix_destroy(&m);
    return EXIT_SUCCESS;
}

#endif
