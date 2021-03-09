#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <main.h>

static int sum_cal(struct Matrix *m, int r, int c) {
    int sum = 0;
    int row;

    for (row = 0; row < r; ++row) {
        sum += matrix_get(m, row, c);
    }
    return sum / r;
}

static int max_row(struct Matrix *m, int r) {
    int max = INT_MIN;
    int col;

    for (col = 0; col < m->cols; ++col) {
        int v = matrix_get(m, r, col);
        if (v > max) {
            max = v;
        }
    }
    return max;
}

struct Matrix *matrix_transform_3(struct Matrix *a, struct Matrix *b, int p, int y) {
    struct Matrix *aa = matrix_dup(a);
    struct Matrix *bb = matrix_dup(b);
    struct Matrix *nab;

#if defined(DEBUG_PRINT)
    matrix_print(aa, stdout);
    fprintf(stdout, "\n\n");
    matrix_print(bb, stdout);
    fprintf(stdout, "\n\n");
#endif

    --p;
    while (p > 0) {
        struct Matrix *na = matrix_mul(aa, a);
        matrix_destroy(&aa);
        aa = na;
        --p;
    }
#if defined(DEBUG_PRINT)
    matrix_print(aa, stdout);
    fprintf(stdout, "\n\n");
#endif
    --y;
    while (y > 0) {
        struct Matrix *nb = matrix_mul(bb, b);
        matrix_destroy(&bb);
        bb = nb;
        --y;
    }
#if defined(DEBUG_PRINT)
    matrix_print(bb, stdout);
    fprintf(stdout, "\n\n");
#endif
    nab = matrix_mul(aa, bb);
#if defined(DEBUG_PRINT)
    matrix_print(nab, stdout);
    fprintf(stdout, "\n\n");
#endif
    matrix_destroy(&aa);
    matrix_destroy(&bb);
    return nab;
}

void matrix_transform_2(struct Matrix *a, int grow) {
    if (a->rows >= grow) {
        return;
    }
    int col, row;
    struct Matrix *m = matrix_create(grow, grow, a->type);
    matrix_copy(m, a);

    for (row = a->rows; row < grow; ++row) {
        for (col = 0; col < a->cols; ++col) {
            int sum = sum_cal(m, row, col);
            matrix_put(m, row, col, sum);
        }
    }

    for (row = 0; row < grow; ++row) {
        for (col = a->cols; col < grow; ++col) {
            int max = max_row(m, row);
            matrix_put(m, row, col, max);
        }
    }



    matrix_destroy(&a);
    a = calloc(1, sizeof(struct Matrix));
    a->data = m->data;
    a->rows = m->rows;
    a->cols = m->cols;
    a->type = m->type;
}

void matrix_transform_1(struct Matrix *a) {
    int c = 0, row = 0, col = 0;
    if (a->rows > a->cols) {
        //Удаление строк
        c = a->rows - a->cols;
        while (c > 0) {
            matrix_find_max(a, FIND_FIRST_COL, &row, &col);
            matrix_delete_col(a, col);
            --c;
        }
    } else {
        //Удаление столбцов
        c = a->cols - a->rows;
        while (c > 0) {
            matrix_find_max(a, FIND_FIRST_COL, &row, &col);
            matrix_delete_row(a, row);
            --c;
        }
    }
}

#if defined(ENTRY_POINT)

int main(int argc, char **argv) {
    struct Matrix *a = 0;
    struct Matrix *b = 0;
    int p = 0, y = 0;
    int max_c;

    /*NOTICE: Ввод матриц осуществялется по схеме загрузки из файла - простой формат*/
    fprintf(stdout, "in A  >");
    a = fread_matrix(stdin, MATRIX_MEMORY_PLAIN);
    fprintf(stdout, "in B  >");
    b = fread_matrix(stdin, MATRIX_MEMORY_PLAIN);
    fprintf(stdout, "in p,y>");
    fscanf(stdin, "%d %d", &p, &y);
    fprintf(stdout, "out   >");

    matrix_transform_1(a);
    matrix_transform_1(b);

    if (a->rows > b->rows) {
        matrix_transform_2(b, a->rows);
    } else {
        matrix_transform_2(a, b->rows);
    }

    matrix_destroy(&a);
    matrix_destroy(&b);
    return EXIT_SUCCESS;
}

#endif
