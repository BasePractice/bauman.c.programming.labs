#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <main.h>

START_TEST(unit_format_x)
    {
        char origin[256];
        char modify[256];
        int  write_origin;
        int  write_modify;


        write_origin = snprintf(origin, sizeof(origin), "%x", 60);
        write_modify = my_snprintf(modify, sizeof(modify), "%x", 60);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%lx", 65535);
        write_modify = my_snprintf(modify, sizeof(modify), "%lx", 65535);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%x %x", 65535, 65535);
        write_modify = my_snprintf(modify, sizeof(modify), "%x %x", 65535, 65535);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%lx %lx", 1L, 1L);
        write_modify = my_snprintf(modify, sizeof(modify), "%lx %lx", 1L, 1L);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, 5, "%lx,%lx,%lx,%lx,%lx", 1, 1, 1, 1, 1);
        write_modify = my_snprintf(modify, 5, "%lx,%lx,%lx,%lx,%lx", 1, 1, 1, 1, 1);
        ck_assert_int_eq(write_origin, write_modify);
    }
END_TEST

START_TEST(unit_format_d)
    {
        char origin[256];
        char modify[256];
        int  write_origin;
        int  write_modify;


        write_origin = snprintf(origin, sizeof(origin), "%d", 60);
        write_modify = my_snprintf(modify, sizeof(modify), "%d", 60);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%ld", 60);
        write_modify = my_snprintf(modify, sizeof(modify), "%ld", 60);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%d %d", 1, 1);
        write_modify = my_snprintf(modify, sizeof(modify), "%d %d", 1, 1);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%ld %ld", 1L, 1L);
        write_modify = my_snprintf(modify, sizeof(modify), "%ld %ld", 1L, 1L);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, 5, "%ld,%ld,%ld,%ld,%ld", 1, 1, 1, 1, 1);
        write_modify = my_snprintf(modify, 5, "%ld,%ld,%ld,%ld,%ld", 1, 1, 1, 1, 1);
        ck_assert_int_eq(write_origin, write_modify);
    }
END_TEST

START_TEST(unit_format_c)
    {
        char origin[256];
        char modify[256];
        int  write_origin;
        int  write_modify;


        write_origin = snprintf(origin, sizeof(origin), "%c", 60);
        write_modify = my_snprintf(modify, sizeof(modify), "%c", 60);
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%c %c", '1', '1');
        write_modify = my_snprintf(modify, sizeof(modify), "%c %c", '1', '1');
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "Modify %c", '1');
        write_modify = my_snprintf(modify, sizeof(modify), "Modify %c", '1');
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, 5, "%c,%c,%c,%c,%c", '1', '1', '1', '1', '1');
        write_modify = my_snprintf(modify, 5, "%c,%c,%c,%c,%c", '1', '1', '1', '1', '1');
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, 5);
    }
END_TEST

START_TEST(unit_format_s)
    {
        char origin[256];
        char modify[256];
        int  write_origin;
        int  write_modify;


        write_origin = snprintf(origin, sizeof(origin), "%s", "Tone");
        write_modify = my_snprintf(modify, sizeof(modify), "%s", "Tone");
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "%s %s", "Tone Tone", "Tone Tone");
        write_modify = my_snprintf(modify, sizeof(modify), "%s %s", "Tone Tone", "Tone Tone");
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, sizeof(origin), "Modify %s", "Tone");
        write_modify = my_snprintf(modify, sizeof(modify), "Modify %s", "Tone");
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);

        write_origin = snprintf(origin, 5, "%s", "Uno Uno Uno");
        write_modify = my_snprintf(modify, 5, "%s", "Uno Uno Uno");
        ck_assert_int_eq(write_origin, write_modify);
        ck_assert_mem_eq(origin, modify, write_modify);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_format");
    tcase_add_test(core_case, unit_format_s);
    tcase_add_test(core_case, unit_format_c);
    tcase_add_test(core_case, unit_format_d);
    tcase_add_test(core_case, unit_format_x);
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
