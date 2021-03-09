#include <stdlib.h>
#include <check.h>
#include "../_inc/main.h"

void mysort(void *begin, size_t elements, size_t element_size, int (*compare_fn)(const void *, const void *));

static int sorted_right[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static int sorted_left[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static int unsorted[] = {9, 1, 7, 3, 4, 5, 6, 2, 8, 0};

START_TEST(unit_sort)
    {
        ck_assert_mem_ne(sorted_right, unsorted, sizeof(sorted_right) / sizeof(sorted_right[0]));
        mysort(unsorted, sizeof(unsorted) / sizeof(unsorted[0]), sizeof(unsorted[0]), compare_int_fn);
#if defined(RIGHT)
        ck_assert_mem_eq(sorted_right, unsorted, sizeof(sorted_left) / sizeof(sorted_left[0]));
#else
        ck_assert_mem_eq(sorted_left, unsorted, sizeof(sorted_left) / sizeof(sorted_left[0]));
#endif
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Sort");
    core_case = tcase_create("unit_sort");
    tcase_add_test(core_case, unit_sort);
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
