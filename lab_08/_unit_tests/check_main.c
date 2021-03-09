#include <stdlib.h>
#include <check.h>
#include <main.h>

#define UNIT_MATRIX_FILENAME "unit_fread_matrix.txt"

struct Matrix *fread_coord_matrix(FILE *fd, enum MatrixMemoryType type);

struct Matrix *fread_plain_matrix(FILE *fd, enum MatrixMemoryType type);

void fwrite_coord_matrix(FILE *fd, struct Matrix *m);

void fwrite_plain_matrix(FILE *fd, struct Matrix *m);

START_TEST(unit_fread_matrix)
    {
        struct Matrix *m;
        FILE *fd = fopen(UNIT_MATRIX_FILENAME, "w+");
        ck_assert_ptr_nonnull(fd);
        fprintf(fd, "2 3\n");
        fprintf(fd, "0 1 2\n");
        fprintf(fd, "3 4 5");
        rewind(fd);
        m = fread_plain_matrix(fd, MATRIX_MEMORY_PLAIN);
        ck_assert_int_eq(m->cols, 3);
        ck_assert_int_eq(m->rows, 2);

        ck_assert_int_eq(matrix_get(m, 0, 0), 0);
        ck_assert_int_eq(matrix_get(m, 0, 1), 1);
        ck_assert_int_eq(matrix_get(m, 0, 2), 2);
        ck_assert_int_eq(matrix_get(m, 1, 0), 3);
        ck_assert_int_eq(matrix_get(m, 1, 1), 4);
        ck_assert_int_eq(matrix_get(m, 1, 2), 5);
        matrix_destroy(&m);
        rewind(fd);
        fprintf(fd, "2 2 3\n");
        fprintf(fd, "1 1 1\n");
        fprintf(fd, "1 2 2\n");
        fprintf(fd, "2 1 3");
        rewind(fd);
        m = fread_coord_matrix(fd, MATRIX_MEMORY_PLAIN);
        ck_assert_int_eq(m->cols, 2);
        ck_assert_int_eq(m->rows, 2);
        ck_assert_int_eq(matrix_get(m, 0, 0), 1);
        ck_assert_int_eq(matrix_get(m, 0, 1), 2);
        ck_assert_int_eq(matrix_get(m, 1, 0), 3);
        matrix_destroy(&m);
        fclose(fd);
        remove(UNIT_MATRIX_FILENAME);
    }
END_TEST

START_TEST(unit_fwrite_matrix)
    {
        FILE *fd = fopen(UNIT_MATRIX_FILENAME, "w+");
        ck_assert_ptr_nonnull(fd);
        fprintf(fd, "2 2 3\n");
        fprintf(fd, "1 1 1\n");
        fprintf(fd, "1 2 2\n");
        fprintf(fd, "2 1 3");
        rewind(fd);

        fclose(fd);
        remove(UNIT_MATRIX_FILENAME);
    }
END_TEST

START_TEST(unit_matrix_find_max)
    {
        struct Matrix *m = matrix_create(2, 3, MATRIX_MEMORY_PLAIN);
        int row = 0, col = 0;

        matrix_put(m, 0, 0, 4);
        matrix_put(m, 0, 1, 7);
        matrix_put(m, 0, 2, 1);
        matrix_put(m, 1, 0, 3);
        matrix_put(m, 1, 1, 2);
        matrix_put(m, 1, 2, 7);
        matrix_find_max(m, FIND_FIRST_ROW, &row, &col);
        ck_assert_int_eq(row, 0);
        ck_assert_int_eq(col, 1);
        matrix_destroy(&m);

        m = matrix_create(5, 3, MATRIX_MEMORY_PLAIN);
        matrix_put(m, 0, 0, 0);
        matrix_put(m, 0, 1, 2);
        matrix_put(m, 0, 2, 9);
        matrix_put(m, 1, 0, 1);
        matrix_put(m, 1, 1, 2);
        matrix_put(m, 1, 2, 2);
        matrix_put(m, 2, 0, 3);
        matrix_put(m, 2, 1, 3);
        matrix_put(m, 2, 2, 3);
        matrix_put(m, 3, 0, 8);
        matrix_put(m, 3, 1, 8);
        matrix_put(m, 3, 2, 2);
        matrix_put(m, 4, 0, 1);
        matrix_put(m, 4, 1, 8);
        matrix_put(m, 4, 2, 3);

        matrix_find_max(m, FIND_FIRST_ROW, &row, &col);
        ck_assert_int_eq(row, 0);
        ck_assert_int_eq(col, 2);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_matrix");
    tcase_add_test(core_case, unit_fread_matrix);
    tcase_add_test(core_case, unit_fwrite_matrix);
    tcase_add_test(core_case, unit_matrix_find_max);
    suite_add_tcase(suite, core_case);
    return suite;
}

int main() {
    Suite *suite;
    SRunner *runner;
    int failed;

    suite = main_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
