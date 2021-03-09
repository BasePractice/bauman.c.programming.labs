#include <stdlib.h>
#include <check.h>
#include <main.h>


void matrix_transform_1(struct Matrix *a);

void matrix_transform_2(struct Matrix *a, int grow);

struct Matrix *matrix_transform_3(struct Matrix *a, struct Matrix *b, int p, int y);

START_TEST(unit_matrix_transform_1)
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
        matrix_delete_col(m, 1);
        ck_assert_int_eq(matrix_get(m, 1, 1), 7);
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

        matrix_delete_row(m, 0);
        matrix_find_max(m, FIND_FIRST_ROW, &row, &col);
        ck_assert_int_eq(row, 2);
        ck_assert_int_eq(col, 0);
        matrix_delete_row(m, 2);

        ck_assert_int_eq(matrix_get(m, 1, 0), 3);
        matrix_destroy(&m);
    }
END_TEST

START_TEST(unit_matrix_transform_2)
    {
        struct Matrix *m = matrix_create(2, 2, MATRIX_MEMORY_PLAIN);

        matrix_put(m, 0, 0, 4);
        matrix_put(m, 0, 1, 1);
        matrix_put(m, 1, 0, 3);
        matrix_put(m, 1, 1, 7);

        matrix_transform_2(m, 3);
        ck_assert_int_eq(matrix_get(m, 0, 2), 4);
        ck_assert_int_eq(matrix_get(m, 1, 2), 7);
        ck_assert_int_eq(matrix_get(m, 2, 0), 3);
        ck_assert_int_eq(matrix_get(m, 2, 1), 4);
        ck_assert_int_eq(matrix_get(m, 2, 2), 4);
        matrix_destroy(&m);
    }
END_TEST

START_TEST(unit_matrix_mul)
    {
        struct Matrix *a = matrix_create(2, 2, MATRIX_MEMORY_PLAIN);
        struct Matrix *b = matrix_create(2, 2, MATRIX_MEMORY_PLAIN);
        struct Matrix *c;

        matrix_put(a, 0, 0, 1);
        matrix_put(a, 0, 1, 2);
        matrix_put(a, 1, 0, 3);
        matrix_put(a, 1, 1, 4);

        matrix_put(b, 0, 0, 1);
        matrix_put(b, 0, 1, 2);
        matrix_put(b, 1, 0, 5);
        matrix_put(b, 1, 1, 3);

        c = matrix_mul(a, b);

        ck_assert_int_eq(matrix_get(c, 0, 0), 11);
        ck_assert_int_eq(matrix_get(c, 0, 1), 8);
        ck_assert_int_eq(matrix_get(c, 1, 0), 23);
        ck_assert_int_eq(matrix_get(c, 1, 1), 18);

        matrix_destroy(&a);
        matrix_destroy(&b);
        matrix_destroy(&c);
    }
END_TEST

START_TEST(unit_matrix_transform_3)
    {
        struct Matrix *a = matrix_create(3, 3, MATRIX_MEMORY_PLAIN);
        struct Matrix *b = matrix_create(3, 3, MATRIX_MEMORY_PLAIN);
        struct Matrix *c;

        matrix_put(a, 0, 0, 4);
        matrix_put(a, 0, 1, 1);
        matrix_put(a, 0, 2, 4);
        matrix_put(a, 1, 0, 3);
        matrix_put(a, 1, 1, 7);
        matrix_put(a, 1, 2, 7);
        matrix_put(a, 2, 0, 3);
        matrix_put(a, 2, 1, 4);
        matrix_put(a, 2, 2, 4);

        matrix_put(b, 0, 0, 1);
        matrix_put(b, 0, 1, 2);
        matrix_put(b, 0, 2, 2);
        matrix_put(b, 1, 0, 3);
        matrix_put(b, 1, 1, 3);
        matrix_put(b, 1, 2, 3);
        matrix_put(b, 2, 0, 1);
        matrix_put(b, 2, 1, 8);
        matrix_put(b, 2, 2, 3);

        c = matrix_transform_3(a, b, 2, 3);

        ck_assert_int_eq(matrix_get(c, 0, 0), 15464);
        ck_assert_int_eq(matrix_get(c, 2, 2), 32461);

        matrix_destroy(&a);
        matrix_destroy(&b);
        matrix_destroy(&c);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_transform");
    tcase_add_test(core_case, unit_matrix_transform_1);
    tcase_add_test(core_case, unit_matrix_transform_2);
    tcase_add_test(core_case, unit_matrix_transform_3);
    tcase_add_test(core_case, unit_matrix_mul);
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