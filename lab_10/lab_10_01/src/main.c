#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <main.h>
#include <struct.h>
#include <fn_find.h>
#include <fn_pop_front.h>
#include <fn_pop_back.h>
#include <fn_insert.h>
#include <fn_copy.h>
#include <fn_append.h>
#include <fn_remove_duplicates.h>
#include <fn_reverse.h>
#include <fn_sort.h>

void callback_create_record(const char **fields, void *userdata) {
    struct Node **root = (struct Node **) userdata;
    node_append(root, (void *) strdup(fields[0]));
}

void print_element(void *data, FILE *fd) {
    if (0 != data) {
        fprintf(fd, "Node: %s\n", (char *) data);
    }
}

static void destroy_element(void *element) {
    if (0 != element) {
        free(element);
    }
}

static void destroy_none(void *element) {
}

int copy_allocate(struct Node *root, struct Node **cpy) {
    struct Node *it = root;

    while (0 != it) {
        node_append(cpy, strdup(it->data));
        it = it->next;
    }
    return 0;
}

int main(int argc, char **argv) {
    FILE *in;
    FILE *out;
    struct Node *root = 0;
    int ret = EXIT_SUCCESS;
    char *function;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s IN_FILE OUT_FILE FUNCTION [ARGS]\n", argv[0]);
        return EXIT_FAILURE;
    }
    in = fopen(argv[1], "r");
    if (0 == in) {
        fprintf(stderr, "IN_FILE can't opened\n");
        return EXIT_FAILURE;
    }
    out = fopen(argv[2], "w+");
    if (0 == out) {
        fclose(in);
        fprintf(stderr, "OUT_FILE can't opened\n");
        return EXIT_FAILURE;
    }
    function = argv[3];

    fread_struct(in, 1, callback_create_record, &root);
    if (strcmp("find", function) == 0) {
        if (argc == 5) {
            struct Node *found = find(root, argv[4], comparator);
            if (0 == found) {
                fprintf(out, "Not found\n");
            } else {
                print_element(found, out);
            }
        } else {
            fprintf(out, "Function arguments not defined\n");
        }
    } else if (strcmp("pop_front", function) == 0) {
        void *pop = pop_front(&root);
        if (0 == pop) {
            fprintf(out, "Empty\n");
        } else {
            fprintf(out, "Node: %s\n", (char *) pop);
            fprintf(out, "--------\n");
            node_foreach(root, (void (*)(void *, void *)) print_element, out);
        }
    } else if (strcmp("pop_back", function) == 0) {
        void *pop = pop_back(&root);
        if (0 == pop) {
            fprintf(out, "Empty\n");
        } else {
            fprintf(out, "Node: %s\n", (char *) pop);
            fprintf(out, "--------\n");
            node_foreach(root, (void (*)(void *, void *)) print_element, out);
        }
    } else if (strcmp("insert", function) == 0) {
        if (argc == 6) {
            struct Node *before = find(root, argv[5], comparator);

            if (0 == before) {
                fprintf(out, "Node \"%s\" not found\n", argv[5]);
            } else {
                struct Node *node = node_create(strdup(argv[4]));
                insert(&root, node, before);
                node_foreach(root, (void (*)(void *, void *)) print_element, out);
            }
        }
    } else if (strcmp("copy", function) == 0) {
        struct Node *cpy = 0;

        copy(root, &cpy);
        node_foreach(cpy, (void (*)(void *, void *)) print_element, out);
        node_destroy(&cpy, destroy_none);
    } else if (strcmp("append", function) == 0) {
        struct Node *cpy = 0;

        copy_allocate(root, &cpy);
        append(&root, &cpy);
        node_foreach(root, (void (*)(void *, void *)) print_element, out);
    } else if (strcmp("remove_duplicates", function) == 0) {

        remove_duplicates(&root,comparator);
        node_foreach(root, (void (*)(void *, void *)) print_element, out);
    } else if (strcmp("reverse", function) == 0) {

        root = reverse(root);
        node_foreach(root, (void (*)(void *, void *)) print_element, out);
    } else if (strcmp("sort", function) == 0) {

        root = sort(root, comparator);
        node_foreach(root, (void (*)(void *, void *)) print_element, out);
    }
    node_destroy(&root, destroy_element);
    fclose(in);
    fclose(out);
    return ret;
}
