#include <stdlib.h>
#include <check.h>
#include "../_inc/main.h"
#include <functions.h>

#define DLL_FN_NAME DLL_LIBRARY_PREFIX PROJECT_NAME DLL_LIBRARY_SUFFIX
#define DLL_FN_EXPORT_PRIME "export_prime"
#define DLL_FN_COPY "copy"

typedef void (*pfn_Export_Prime)(long long *dst, size_t dst_size);

typedef size_t (*pfn_Copy)(long long *dst, size_t dst_size, const long long *src, size_t src_size);

START_TEST(unit_fn_prime)
    {
        long long primes[256];
        void *l = llibrary_load(DLL_FN_NAME);
        pfn_Export_Prime ep = (pfn_Export_Prime) llibrary_sym(l, DLL_FN_EXPORT_PRIME);

        (*ep)(primes, sizeof(primes) / sizeof(primes[0]));
        ck_assert_int_eq(primes[0], 2L);
        ck_assert_int_eq(primes[1], 3L);
        ck_assert_int_eq(primes[2], 5L);
        ck_assert_int_eq(primes[3], 7L);
        ck_assert_int_eq(primes[4], 11L);

        memset(primes, 0, sizeof(primes));
        (*ep)(primes, 2);
        ck_assert_int_eq(primes[0], 2L);
        ck_assert_int_eq(primes[1], 3L);
        ck_assert_int_eq(primes[2], 0L);

        llibrary_free(l);
    }
END_TEST

#define RESET(dst) memset(dst, 0, sizeof(dst))

START_TEST(unit_fn_copy)
    {
        long long dst[256];
        long long src[] = {1, 2, 1, 2, 2, 3, 2, 4};
        size_t ret;
        void *l = llibrary_load(DLL_FN_NAME);
        pfn_Copy cpy = (pfn_Copy) llibrary_sym(l, DLL_FN_COPY);

        RESET(dst);
        ret = (*cpy)(dst, sizeof(dst) / sizeof(dst[0]), src, sizeof(src) / sizeof(src[0]));
        ck_assert_int_eq(ret, 4);
        ck_assert_int_eq(dst[0], 1);
        ck_assert_int_eq(dst[1], 2);
        ck_assert_int_eq(dst[2], 3);
        ck_assert_int_eq(dst[3], 4);

        RESET(dst);
        ret = (*cpy)(0, sizeof(dst) / sizeof(dst[0]), src, sizeof(src) / sizeof(src[0]));
        ck_assert_int_eq(ret, 4);
        ret = (*cpy)(dst, 4, src, sizeof(src) / sizeof(src[0]));
        ck_assert_int_eq(ret, 4);
        ck_assert_int_eq(dst[0], 1);
        ck_assert_int_eq(dst[1], 2);
        ck_assert_int_eq(dst[2], 3);
        ck_assert_int_eq(dst[3], 4);

        llibrary_free(l);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Filter");
    core_case = tcase_create("unit_function");
    tcase_add_test(core_case, unit_fn_prime);
    tcase_add_test(core_case, unit_fn_copy);
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

