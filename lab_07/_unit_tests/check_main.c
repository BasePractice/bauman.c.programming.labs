#include <stdlib.h>
#include <check.h>
#include "../_inc/main.h"

#define UNIT_MATRIX_FILENAME "unit_fget_numbers.txt"
#define WRITE_SEQUENCE(fd, sequence) \
    rewind((fd));                    \
    fprintf((fd), sequence);         \
    rewind((fd));

START_TEST(unit_fget_numbers)
    {
    bool ok = true;
        FILE *fd = fopen(UNIT_MATRIX_FILENAME, "w+");
        ck_assert_ptr_nonnull(fd);
        WRITE_SEQUENCE(fd, "10");
        ck_assert_int_eq(1, fget_numbers(fd, &ok));
        ck_assert(ok);
        WRITE_SEQUENCE(fd, "10    14 2     3");
        ck_assert_int_eq(4, fget_numbers(fd, &ok));
        ck_assert(ok);
        WRITE_SEQUENCE(fd, "\n\n1\n\n\n\n\n3\n\n\n\n\n\n\n\n\n");
        ck_assert_int_eq(2, fget_numbers(fd, &ok));
        ck_assert(ok);
        WRITE_SEQUENCE(fd, "aaaaaaaaaaa");
        ck_assert_int_eq(0, fget_numbers(fd, &ok));
        ck_assert(ok == false);
        fclose(fd);
        remove(UNIT_MATRIX_FILENAME);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_fget_numbers");
    tcase_add_test(core_case, unit_fget_numbers);
    suite_add_tcase(suite, core_case);
    return suite;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst) {
    return 0;
}

void mysort(void *begin, size_t elements, size_t element_size, int (*compare_fn)(const void *, const void *)) {

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
