#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <main.h>
#include <struct.h>

struct Build {
    struct List *list;
    char *prefix;
};

void destroy_free(void *element) {
    if (0 != element) {
        struct Thing *h = (struct Thing *) element;
        if (0 != h->name)
            free(h->name);
        free(element);
    }
}

int compare_Thing_fn(void *a, void *b, void *userdata) {
    struct Thing *ah = (struct Thing *) a;
    struct Thing *bh = (struct Thing *) b;
    double ap = ah->mass / ah->volume;
    double bp = bh->mass / bh->volume;
    if (ap > bp) {
        return 1;
    } else if (ap < bp) {
        return -1;
    }
    return 0;
}

void build_record(const char **fields, void *userdata) {
    struct Build *build = (struct Build *) userdata;
    struct Thing *thing = calloc(1, sizeof(struct Thing));
    if (0 == build->list)
        return;
    thing->name = strdup(fields[0]);
    thing->mass = strtod(fields[1], 0);
    thing->volume = strtod(fields[2], 0);
    list_append_sort(build->list, thing, compare_Thing_fn, build->prefix);
}

void print_element(void *element, void *userdata) {
    struct Thing *thing = (struct Thing *) element;
    if (0 != thing) {
        fprintf(stdout, "Name  : %s\n", thing->name);
        fprintf(stdout, "Mass  : %f\n", thing->mass);
        fprintf(stdout, "Volume: %f\n", thing->volume);
    }
}

void print_filter(void *element, void *filter) {
    struct Thing *thing = (struct Thing *) element;
    if (0 != thing && !strncmp(thing->name, filter, strlen(filter))) {
        fprintf(stdout, "Name  : %s\n", thing->name);
        fprintf(stdout, "Mass  : %f\n", thing->mass);
        fprintf(stdout, "Volume: %f\n", thing->volume);
    }
}

int main(int argc, char **argv) {
    FILE *in;
    int ret = EXIT_SUCCESS;
    struct List list = {0};
    struct Build build = {&list, 0};

    if (argc < 2) {
        fprintf(stderr, "Usage: %s FILE [PREFIX]\n", argv[0]);
        return EXIT_FAILURE;
    }
    in = fopen(argv[1], "r");
    if (0 == in) {
        fprintf(stderr, "IN_FILE can't opened\n");
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        build.prefix = argv[2];
    }

    fread_struct(in, 3, build_record, &build);
    if (0 != build.prefix) {
        if (!stricmp("ALL", build.prefix)) {
            list_foreach(&list, print_element, 0);
            fprintf(stdout, "\n");
            fflush(stdout);
        } else {
            list_foreach(&list, print_filter, build.prefix);
            fprintf(stdout, "\n");
            fflush(stdout);
        }
    } else {
        list_foreach(&list, print_element, 0);
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    list_destroy(&list, destroy_free);
    fclose(in);
    return ret;
}
