#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <main.h>

#define DLL_FN_NAME DLL_LIBRARY_PREFIX "dummy_lib" DLL_LIBRARY_SUFFIX

typedef char *(*pfn_Dummy)();

START_TEST(unit_llibrary)
    {
        void *l = llibrary_load(DLL_FN_NAME);
        ck_assert_ptr_nonnull(l);
        pfn_Dummy dummy = (pfn_Dummy) llibrary_sym(l, "dummy");
        ck_assert_ptr_nonnull(dummy);
        ck_assert_mem_eq((*dummy)(), "dummy", 5);
        llibrary_free(l);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_dll");
    tcase_add_test(core_case, unit_llibrary);
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
