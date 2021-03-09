#include <stdlib.h>
#include <check.h>
#include <main.h>

#define UNIT_MATRIX_FILENAME "unit_fread_struct.txt"

static void destroy_none(void *element) {

}

void callback_fread_struct(const char **fields, void *userdata) {
    ck_assert(strcmp(fields[0], "One") == 0);
    ck_assert(strcmp(fields[1], "Two") == 0);
    ck_assert(strcmp(fields[2], "Three") == 0);
}

START_TEST(unit_fread_struct)
    {
        FILE *fd = fopen(UNIT_MATRIX_FILENAME, "w+");
        ck_assert_ptr_nonnull(fd);
        fprintf(fd, "One\n");
        fprintf(fd, "Two\n");
        fprintf(fd, "Three");
        rewind(fd);
        fread_struct(fd, 3, callback_fread_struct, 0);
        fclose(fd);
        remove(UNIT_MATRIX_FILENAME);
    }
END_TEST

START_TEST(unit_node_append)
    {
    struct Node *root = 0;

    node_append(&root, "One");
    node_append(&root, "Two");
    node_append(&root, "Three");

    ck_assert(strcmp("One", root->data) == 0);
    ck_assert(strcmp("Two", root->next->data) == 0);
    ck_assert(strcmp("Three", root->next->next->data) == 0);

    node_destroy(&root, destroy_none);
    ck_assert_ptr_null(root);
    }
END_TEST

START_TEST(unit_node_next)
    {

        struct Node *root = 0;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        ck_assert(node_next(root, 4) == 0);
        ck_assert(strcmp((char *)node_next(root, 0)->data, "One") == 0);
        ck_assert(strcmp((char *)node_next(root, 1)->data, "Two") == 0);
        ck_assert(strcmp((char *)node_next(root, 2)->data, "Three") == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);

    }
END_TEST

START_TEST(unit_node_tail)
    {
        struct Node *root = 0;
        struct Node *prev = 0;

        node_append(&root, "One");
        node_append(&root, "Two");
        node_append(&root, "Three");

        ck_assert(strcmp(node_tail(root, &prev)->data, "Three") == 0);
        ck_assert(strcmp(prev->data, "Two") == 0);
        ck_assert(strcmp(node_tail(root, 0)->data, "Three") == 0);

        node_destroy(&root, destroy_none);
        ck_assert_ptr_null(root);
    }
END_TEST

Suite *main_suite() {
    Suite *suite;
    TCase *core_case;

    suite = suite_create("Main");
    core_case = tcase_create("unit_node");
    tcase_add_test(core_case, unit_node_append);
    tcase_add_test(core_case, unit_node_next);
    tcase_add_test(core_case, unit_node_tail);
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
