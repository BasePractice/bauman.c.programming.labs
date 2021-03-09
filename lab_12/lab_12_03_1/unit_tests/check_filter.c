#include <stdlib.h>
#include <check.h>
#include "../_inc/main.h"

int key(const int *pb_src, const int *pe_src, int *pb_dst, int size);
typedef int (*pfn_Key)(const int *pb_src, const int *pe_src, int *pb_dst, int size);

static int without_neg[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static int without_neg_filtered[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static int with_neg[] = {3, 1, 7, 9, 4, -5, 6, 2, 8, 0};
static int with_neg_filtered[] = {3, 1, 7, 9, 4};

#define DLL_FN_NAME DLL_LIBRARY_PREFIX PROJECT_NAME "_shared" DLL_LIBRARY_SUFFIX

START_TEST(unit_static)
    {
        int *filtered = calloc(256, sizeof(int));
        int filtered_c;

        filtered_c = key(without_neg, without_neg + 10, filtered, 256);
        ck_assert_int_eq(filtered_c, 0);
        ck_assert_mem_eq(without_neg_filtered, filtered, filtered_c * sizeof(int));

        filtered_c = key(with_neg, with_neg + 10, filtered, 256);
        ck_assert_int_eq(filtered_c, 0);
        ck_assert_mem_eq(with_neg_filtered, filtered, filtered_c * sizeof(int));

        filtered_c = key(with_neg, with_neg, filtered, 256);
        ck_assert_int_eq(filtered_c, 0);

        filtered_c = key(with_neg, with_neg + 10, filtered, 1);
        ck_assert_int_eq(filtered_c, 5);
        filtered_c = key(with_neg, with_neg + 5, filtered, 256);
        ck_assert_int_eq(filtered_c, 0);
        ck_assert_mem_eq(with_neg_filtered, filtered, filtered_c * sizeof(int));

        free(filtered);
    }
END_TEST

START_TEST(unit_dynamic)
    {
        int *filtered = calloc(256, sizeof(int));
        int filtered_c;
        void *l = llibrary_load(DLL_FN_NAME);
        pfn_Key p_key = llibrary_sym(l, "key");

        filtered_c = (*p_key)(without_neg, without_neg + 10, filtered, 256);
        ck_assert_int_eq(filtered_c, 0);
        ck_assert_mem_eq(without_neg_filtered, filtered, filtered_c * sizeof(int));

        filtered_c = (*p_key)(with_neg, with_neg + 10, filtered, 256);
        ck_assert_int_eq(filtered_c, 0);
        ck_assert_mem_eq(with_neg_filtered, filtered, filtered_c * sizeof(int));

        filtered_c = (*p_key)(with_neg, with_neg, filtered, 256);
        ck_assert_int_eq(filtered_c, 0);

        llibrary_free(l);
        free(filtered);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Filter");
    core_case = tcase_create("Core");
    tcase_add_test(core_case, unit_static);
    tcase_add_test(core_case, unit_dynamic);
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
