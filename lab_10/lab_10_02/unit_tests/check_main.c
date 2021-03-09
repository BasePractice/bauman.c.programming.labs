#include <stdlib.h>
#include <check.h>
#include <main.h>
#include <value.h>
#include <text.h>

static void destroy_none(void *element) {

}

static void destroy_element(void *element) {
    if (0 != element) {
        free(element);
    }
}

START_TEST(unit_find)
    {
        struct Node *root = 0;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_pair_polynom_parse)
    {
        struct Node *root = 0;
        char *line = strdup("4 2 1 0");

        pair_polynom_parse(line, &root);
        ck_assert_int_eq(((struct ValuePolynomial *) root->data)->n, 4);
        ck_assert_int_eq(((struct ValuePolynomial *) root->data)->e, 2);
        ck_assert_int_eq(((struct ValuePolynomial *) root->next->data)->n, 1);
        ck_assert_int_eq(((struct ValuePolynomial *) root->next->data)->e, 0);
        free(line);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_uno_polynom_parse)
    {
        struct Node *root = 0;
        char *line = strdup("4 2 1 0");

        ck_assert_int_eq(uno_polynom_parse(line, &root), 4);
        ck_assert_int_eq((long long)root->data, 4);
        ck_assert_int_eq((long long)root->next->data, 2);
        ck_assert_int_eq((long long)root->next->next->data, 1);
        ck_assert_int_eq((long long)root->next->next->next->data, 0);
        free(line);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_text_parse)
    {
        struct Node *root = 0;

        text_parse("Please eat eshche etich", &root);

        ck_assert(strcmp("Plea", root->data) == 0);
        ck_assert(strcmp("se e", root->next->data) == 0);
        ck_assert(strcmp("at e", root->next->next->data) == 0);
        ck_assert(strcmp("shch", root->next->next->next->data) == 0);
        ck_assert(strcmp("e et", root->next->next->next->next->data) == 0);
        ck_assert(strcmp("ich", root->next->next->next->next->next->data) == 0);

        node_destroy(&root, destroy_element);
        ck_assert_ptr_null(root);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_function");
    tcase_add_test(core_case, unit_find);
    suite_add_tcase(suite, core_case);

    core_case = tcase_create("unit_value");
    tcase_add_test(core_case, unit_pair_polynom_parse);
    tcase_add_test(core_case, unit_uno_polynom_parse);
    suite_add_tcase(suite, core_case);

    core_case = tcase_create("unit_text");
    tcase_add_test(core_case, unit_text_parse);
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
