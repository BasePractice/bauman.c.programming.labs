#include <stdlib.h>
#include <check.h>
#include "../_inc/main.h"

void add_element(int **begin, int **end, int element);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

static int sorted[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static int sorted_filter[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static int unsorted[] = {3, 1, 7, 9, 4, -5, 6, 2, 8, 0};
static int unsorted_filter[] = {3, 1, 7, 9, 4};

START_TEST(unit_add_element)
    {
        int *temp_begin = 0;
        int *temp_end = 0;

        add_element(&temp_begin, &temp_end, 0);
        add_element(&temp_begin, &temp_end, 1);
        add_element(&temp_begin, &temp_end, 2);
        add_element(&temp_begin, &temp_end, 3);
        ck_assert_int_eq(*(temp_begin + 0), 0);
        ck_assert_int_eq(*(temp_begin + 1), 1);
        ck_assert_int_eq(*(temp_begin + 2), 2);
        ck_assert_int_eq(*(temp_begin + 3), 3);
        free(temp_begin);
    }
END_TEST

START_TEST(unit_filter)
    {
        int *filter_begin = 0;
        int *filter_end = 0;
        int filtered;

        filtered = key(sorted, sorted + 10, &filter_begin, &filter_end);
        ck_assert_int_eq(filtered, 10);
        ck_assert_mem_eq(sorted_filter, filter_begin, (filter_end - filter_begin) * sizeof(int));
        free(filter_begin);

        filter_begin = 0;
        filter_end = 0;
        filtered = key(unsorted, unsorted + 10, &filter_begin, &filter_end);
        ck_assert_int_eq(filtered, 5);
        ck_assert_mem_eq(unsorted_filter, filter_begin, (filter_end - filter_begin) * sizeof(int));
        free(filter_begin);

        filter_begin = 0;
        filter_end = 0;
        filtered = key(unsorted, unsorted, &filter_begin, &filter_end);
        ck_assert_int_eq(filtered, 0);
        ck_assert_ptr_null(filter_begin);
        ck_assert_ptr_null(filter_end);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Filter");
    core_case = tcase_create("Core");
    tcase_add_test(core_case, unit_add_element);
    tcase_add_test(core_case, unit_filter);
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
