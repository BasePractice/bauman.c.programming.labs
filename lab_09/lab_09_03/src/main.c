#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <main.h>
#include <struct.h>

void destroy_free(void *element) {
    if (0 != element) {
        struct Product *p = (struct Product *) element;
        if (0 != p->name)
            free(p->name);
        free(element);
    }
}

int compare_Product_fn(void *a, void *b, void *userdata) {
    struct Product *ap = (struct Product *) a;
    struct Product *bp = (struct Product *) b;
    if (ap->price > bp->price) {
        return 1;
    } else if (ap->price < bp->price) {
        return -1;
    }
    return 0;
}

void build_record(const char **fields, void *userdata) {
    struct List *list = (struct List *) userdata;
    struct Product *product = calloc(1, sizeof(struct Product));
    product->name = strdup(fields[0]);
    product->price = strtol(fields[1], 0, 10);
    list_append_sort(list, product, compare_Product_fn, 0);
}

void print_element(void *element, void *userdata) {
    struct Product *product = (struct Product *) element;
    if (0 != product) {
        fprintf(stdout, "Name  : %s\n", product->name);
        fprintf(stdout, "Price : %lu\n", product->price);
    }
}

void print_filter(void *element, void *filter) {
    struct Product *product = (struct Product *) element;
    if (0 != product && product->price > (long long) filter) {
        fprintf(stdout, "Name  : %s\n", product->name);
        fprintf(stdout, "Price : %lu\n", product->price);
    }
}

int main(int argc, char **argv) {
    FILE *in;
    int ret = EXIT_SUCCESS;
    struct List list = {0};

    if (argc < 3) {
        fprintf(stderr, "Usage: %s FILE [PREFIX]\n", argv[0]);
        return EXIT_FAILURE;
    }
    in = fopen(argv[1], "r");
    if (0 == in) {
        fprintf(stderr, "IN_FILE can't opened\n");
        return EXIT_FAILURE;
    }

    fread_struct(in, 2, build_record, &list);
    list_foreach(&list, print_filter, (void *)(long long)strtol(argv[2], 0, 10));
    fprintf(stdout, "\n");
    fflush(stdout);
    list_destroy(&list, destroy_free);
    fclose(in);
    return ret;
}
