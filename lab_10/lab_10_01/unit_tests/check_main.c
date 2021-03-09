#include <stdlib.h>
#include <check.h>
#include <main.h>
#include <fn_find.h>
#include <fn_pop_front.h>
#include <fn_pop_back.h>
#include <fn_insert.h>
#include <fn_copy.h>
#include <fn_append.h>
#include <fn_remove_duplicates.h>
#include <fn_reverse.h>
#include <fn_sort.h>

static void destroy_none(void *element) {

}

START_TEST(unit_find)
    {
        struct Node *root = 0;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        ck_assert(strcmp("One", find(root, "One", comparator)->data) == 0);
        ck_assert(strcmp("Two", find(root, "Two", comparator)->data) == 0);
        ck_assert(strcmp("Three", find(root, "Three", comparator)->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_pop_front)
    {
        struct Node *root = 0;
        void *data;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        data = pop_front(&root);

        ck_assert(strcmp("One", data) == 0);
        ck_assert(strcmp("Two", root->data) == 0);
        ck_assert(strcmp("Three", root->next->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_pop_end)
    {
        struct Node *root = 0;
        void *data;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        data = pop_back(&root);

        ck_assert(strcmp("Three", data) == 0);
        ck_assert(strcmp("One", root->data) == 0);
        ck_assert(strcmp("Two", root->next->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_insert)
    {
        struct Node *root = 0;
        struct Node *before;
        struct Node *node = node_create("None");

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");
        node_append(&root, "Five");

        before = find(root, "Five", comparator);
        ck_assert(strcmp("Five", before->data) == 0);
        insert(&root, node, before);
        before = find(root, "None", comparator);
        ck_assert(strcmp("None", before->data) == 0);
        ck_assert(strcmp("Five", before->next->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_copy)
    {
        struct Node *root = 0;
        struct Node *cpy = 0;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        copy(root, &cpy);

        ck_assert(strcmp("One", cpy->data) == 0);
        ck_assert(strcmp("Two", cpy->next->data) == 0);
        ck_assert(strcmp("Three", cpy->next->next->data) == 0);

        node_destroy(&root, destroy_none);
        node_destroy(&cpy, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_append)
    {
        struct Node *a = 0;
        struct Node *b = 0;

        node_append(&a, "One");
        node_append(&a, "Two");
        node_append(&b, "Three");

        append(&a, &b);

        ck_assert(strcmp("One", a->data) == 0);
        ck_assert(strcmp("Two", a->next->data) == 0);
        ck_assert(strcmp("Three", a->next->next->data) == 0);

        ck_assert_ptr_null(node_tail(b, 0));

        node_destroy(&a, destroy_none);
        node_destroy(&b, destroy_none);
        ck_assert_ptr_null(a);
        ck_assert_ptr_null(b);
    }
END_TEST

START_TEST(unit_remove_duplicates)
    {
        struct Node *root = 0;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Two");
        node_append(&root, "Three");

        remove_duplicates(&root, comparator);

        ck_assert(strcmp("One", root->data) == 0);
        ck_assert(strcmp("Two", root->next->data) == 0);
        ck_assert(strcmp("Three", root->next->next->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_reverse)
    {
        struct Node *root = 0;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        root = reverse(root);

        ck_assert(strcmp("Three", root->data) == 0);
        ck_assert(strcmp("Two", root->next->data) == 0);
        ck_assert(strcmp("One", root->next->next->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_sort)
    {
        struct Node *root = 0;

        node_append(&root, "1");
        node_append(&root, "2");
        node_append(&root, "3");

        root = sort(root, comparator);

        ck_assert(strcmp("3", root->data) == 0);
        ck_assert(strcmp("2", root->next->data) == 0);
        ck_assert(strcmp("1", root->next->next->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);

        node_append(&root, "1");
        node_append(&root, "5");
        node_append(&root, "2");
        node_append(&root, "2");
        node_append(&root, "3");

        root = sort(root, comparator);

        ck_assert(strcmp("5", root->data) == 0);
        ck_assert(strcmp("3", root->next->data) == 0);
        ck_assert(strcmp("2", root->next->next->data) == 0);
        ck_assert(strcmp("2", root->next->next->next->data) == 0);
        ck_assert(strcmp("1", root->next->next->next->next->data) == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_function");
    tcase_add_test(core_case, unit_find);
    tcase_add_test(core_case, unit_pop_front);
    tcase_add_test(core_case, unit_pop_end);
    tcase_add_test(core_case, unit_insert);
    tcase_add_test(core_case, unit_copy);
    tcase_add_test(core_case, unit_append);
    tcase_add_test(core_case, unit_remove_duplicates);
    tcase_add_test(core_case, unit_reverse);
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
