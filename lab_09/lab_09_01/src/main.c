#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <main.h>
#include <struct.h>

struct Build {
    struct List *list;
    char *sort_field;
};

void destroy_free(void *element) {
    if (0 != element) {
        struct Film *f = (struct Film *) element;
        if (0 != f->name)
            free(f->name);
        if (0 != f->title)
            free(f->title);
        free(element);
    }
}

int compare_Film_fn(void *a, void *b, void *field) {
    struct Film *af = (struct Film *) a;
    struct Film *bf = (struct Film *) b;
    if (!strcmp(field, "title")) {
        return strcmp(af->title, bf->title);
    } else if (!strcmp(field, "name")) {
        return strcmp(af->name, bf->name);
    } else if (!strcmp(field, "year")) {
        if (af->year > bf->year) {
            return 1;
        } else if (af->year < bf->year) {
            return -1;
        }
        return 0;
    } else {
        return strcmp(af->title, bf->title);
    }
}

int compare_Field_fn(void *a, void *b, void *field) {
    struct Film *af = (struct Film *) a;
    char *bf = b;
    if (!strcmp(field, "title")) {
        return strcmp(af->title, bf);
    } else if (!strcmp(field, "name")) {
        return strcmp(af->name, bf);
    } else if (!strcmp(field, "year")) {
        long long l = strtol(bf, 0, 10);
        if (af->year > l) {
            return 1;
        } else if (af->year < l) {
            return -1;
        }
        return 0;
    } else {
        return strcmp(af->title, bf);
    }
}

bool eq(struct Film *element, char *field, void *value) {
    if (!strcmp(field, "title")) {
        return strcmp(element->title, value) == 0;
    } else if (!strcmp(field, "name")) {
        return strcmp(element->name, value) == 0;
    } else if (!strcmp(field, "year")) {
        return element->year == strtol(value, 0, 10);
    }
    return false;
}

void build_record(const char **fields, void *userdata) {
    struct Build *build = (struct Build *) userdata;
    struct Film *film = calloc(1, sizeof(struct Film));
    if (0 == build->list)
        return;
    film->title = strdup(fields[0]);
    film->name = strdup(fields[1]);
    film->year = strtol(fields[2], 0, 10);
    list_append_sort(build->list, film, compare_Film_fn, build->sort_field);
}

void print_element(void *element, void *userdata) {
    struct Film *film = (struct Film *) element;
    if (0 != film) {
        fprintf(stdout, "Title: %s\n", film->title);
        fprintf(stdout, "Name : %s\n", film->name);
        fprintf(stdout, "Year : %d\n", film->year);
    }
}

int main(int argc, char **argv) {
    FILE *in;
    int ret = EXIT_SUCCESS;
    struct List list = {0};
    struct Build build = {&list, 0};

    if (argc < 3) {
        fprintf(stderr, "Usage: %s FILE FIELD [KEY]\n", argv[0]);
        return EXIT_FAILURE;
    }
    in = fopen(argv[1], "r");
    if (0 == in) {
        fprintf(stderr, "IN_FILE can't opened\n");
        return EXIT_FAILURE;
    }
    build.sort_field = argv[2];
    fread_struct(in, 3, build_record, &build);
    if (argc == 4) {
        enum BinarySearchSide side = NOT_FOUND;
        ssize_t i = binary_search(&list, 0, list.size - 1, argv[3], &side, compare_Field_fn, argv[2]);
        if (side == FOUND) {
            print_element(list.elements[i], 0);
            fprintf(stdout, "\n");
            fflush(stdout);
        } else {
            fprintf(stdout, "Not found\n");
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
