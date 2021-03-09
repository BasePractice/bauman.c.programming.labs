#include <stdlib.h>
#include <check.h>
#include <main.h>

#define UNIT_MATRIX_FILENAME "unit_fread_struct.txt"

static void destroy_none(void *element) {

}

int compare_long_fn(void *a, void *b, void *userdata) {
    if ((long long) a < (long long) b) return -1;
    if ((long long) a > (long long) b) return 1;
    return 0;
}

void callback_none(const char **fields, void *userdata) {

}

START_TEST(unit_fread_struct)
    {
        FILE *fd = fopen(UNIT_MATRIX_FILENAME, "w+");
        ck_assert_ptr_nonnull(fd);
        fprintf(fd, "One\n");
        fprintf(fd, "Two\n");
        fprintf(fd, "Three");
        rewind(fd);
        fread_struct(fd, 3, callback_none, 0);
        fclose(fd);
        remove(UNIT_MATRIX_FILENAME);
    }
END_TEST

START_TEST(unit_list_insert)
    {
        struct List list = {0};

        list_insert(&list, 0, (void *) (long long) 0);
        list_insert(&list, 0, (void *) (long long) 1);
        list_insert(&list, 0, (void *) (long long) 2);
        list_insert(&list, 0, (void *) (long long) 3);
        ck_assert_int_eq((long long) list.elements[0], (long long) 3);
        ck_assert_int_eq((long long) list.elements[1], (long long) 2);
        ck_assert_int_eq((long long) list.elements[2], (long long) 1);
        ck_assert_int_eq((long long) list.elements[3], (long long) 0);

        list_destroy(&list, destroy_none);
    }
END_TEST

START_TEST(unit_list_append)
    {
        struct List list = {0};

        list_append(&list, (void *) (long long) 0);
        list_append(&list, (void *) (long long) 1);
        list_append(&list, (void *) (long long) 2);
        list_append(&list, (void *) (long long) 3);
        ck_assert_int_eq((long long) list.elements[0], (long long) 0);
        ck_assert_int_eq((long long) list.elements[1], (long long) 1);
        ck_assert_int_eq((long long) list.elements[2], (long long) 2);
        ck_assert_int_eq((long long) list.elements[3], (long long) 3);

        list_destroy(&list, destroy_none);
    }
END_TEST

START_TEST(unit_list_destroy)
    {
        list_destroy(0, destroy_none);
    }
END_TEST

START_TEST(unit_list_append_sort)
    {
        struct List list = {0};

        list_append_sort(&list, (void *) (long long) 3, compare_long_fn, 0);
        ck_assert_int_eq((long long) list.elements[0], (long long) 3);

        list_destroy(&list, destroy_none);

        list_append_sort(&list, (void *) (long long) 3, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 2, compare_long_fn, 0);
        ck_assert_int_eq((long long) list.elements[0], (long long) 3);
        ck_assert_int_eq((long long) list.elements[1], (long long) 2);

        list_destroy(&list, destroy_none);

        list_append_sort(&list, (void *) (long long) 2, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 3, compare_long_fn, 0);
        ck_assert_int_eq((long long) list.elements[0], (long long) 3);
        ck_assert_int_eq((long long) list.elements[1], (long long) 2);

        list_destroy(&list, destroy_none);

        list_append_sort(&list, (void *) (long long) 1, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 2, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 3, compare_long_fn, 0);
        ck_assert_int_eq((long long) list.elements[0], (long long) 3);
        ck_assert_int_eq((long long) list.elements[1], (long long) 2);
        ck_assert_int_eq((long long) list.elements[2], (long long) 1);

        list_destroy(&list, destroy_none);

        list_append_sort(&list, (void *) (long long) 3, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 1, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 2, compare_long_fn, 0);
        ck_assert_int_eq((long long) list.elements[0], (long long) 3);
        ck_assert_int_eq((long long) list.elements[1], (long long) 2);
        ck_assert_int_eq((long long) list.elements[2], (long long) 1);

        list_destroy(&list, destroy_none);

        list_append_sort(&list, (void *) (long long) 3, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 2, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 1, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 8, compare_long_fn, 0);
        ck_assert_int_eq((long long) list.elements[0], (long long) 8);
        ck_assert_int_eq((long long) list.elements[1], (long long) 3);
        ck_assert_int_eq((long long) list.elements[2], (long long) 2);
        ck_assert_int_eq((long long) list.elements[3], (long long) 1);

        list_destroy(&list, destroy_none);

        list_append_sort(&list, (void *) (long long) 3, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 2, compare_long_fn, 0);
        list_append_sort(&list, (void *) (long long) 8, compare_long_fn, 0);
        ck_assert_int_eq((long long) list.elements[0], (long long) 8);
        ck_assert_int_eq((long long) list.elements[1], (long long) 3);
        ck_assert_int_eq((long long) list.elements[2], (long long) 2);

        list_destroy(&list, destroy_none);
    }
END_TEST

START_TEST(unit_binary_search)
    {
        struct List list = {0};
        ssize_t i;
        enum BinarySearchSide side = NOT_FOUND;

        list_append(&list, (void *) (long long) 3);
        list_append(&list, (void *) (long long) 2);
        list_append(&list, (void *) (long long) 1);
        list_append(&list, (void *) (long long) 0);
        i = binary_search(&list, 0, list.size - 1, (void *) (long long) 1, &side, compare_long_fn, 0);
        ck_assert_int_eq(i, 2);
        ck_assert(side == FOUND);
        list_destroy(&list, destroy_none);

        list_append(&list, (void *) (long long) 3);
        list_append(&list, (void *) (long long) 2);
        list_append(&list, (void *) (long long) 1);
        i = binary_search(&list, 0, list.size - 1, (void *) (long long) 2, &side, compare_long_fn, 0);
        ck_assert_int_eq(i, 1);
        ck_assert(side == FOUND);
        list_destroy(&list, destroy_none);

        list_append(&list, (void *) (long long) 30);
        list_append(&list, (void *) (long long) 20);
        list_append(&list, (void *) (long long) 10);
        i = binary_search(&list, 0, list.size - 1, (void *) (long long) 1, &side, compare_long_fn, 0);
        ck_assert(side == RIGHT);
        ck_assert(i > 0);
        list_destroy(&list, destroy_none);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_list");
    tcase_add_test(core_case, unit_list_insert);
    tcase_add_test(core_case, unit_list_append);
    tcase_add_test(core_case, unit_list_destroy);
    tcase_add_test(core_case, unit_list_append_sort);
    tcase_add_test(core_case, unit_binary_search);
    suite_add_tcase(suite, core_case);
    core_case = tcase_create("unit_file");
    tcase_add_test(core_case, unit_fread_struct);
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
