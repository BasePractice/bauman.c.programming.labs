#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "../_inc/main.h"

extern int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

extern void mysort(void *begin, size_t elements, size_t element_size, int (*compare_fn)(const void *, const void *));

int fget_numbers(FILE *fd, bool *ok) {
    int count = 0;
    int ch;
    bool in_number = false;
    (*ok) = true;
    while (!feof(fd) && (ch = fgetc(fd)) != EOF) {
        if (isdigit(ch)) {
            if (!in_number)
                ++count;
            in_number = true;
        } else if (isspace(ch)) {
            in_number = false;
        } else if ('-' == ch) {
            in_number = false;
        } else {
            (*ok) = false;
            break;
        }
    }
    return count;
}

int compare_int_fn(const void *a, const void *b) {
    if (*(int *) a < *(int *) b) return -1;
    if (*(int *) a > *(int *) b) return 1;
    return 0;
}

#if defined(ENTRY_POINT)

int main(int argc, char **argv) {
    FILE *in;
    FILE *out;
    int numbers;
    int ret = EXIT_SUCCESS;
    int *in_array_begin = 0, *in_array_end = 0;
    int *out_array_begin = 0, *out_array_end = 0;
    bool ok = true;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s IN_FILE OUT_FILE [f]\n", argv[0]);
        return EXIT_FAILURE;
    }
    in = fopen(argv[1], "r");
    if (0 == in) {
        fprintf(stderr, "IN_FILE can't opened\n");
        return EXIT_FAILURE;
    }
    out = fopen(argv[2], "w");
    if (0 == out) {
        fclose(in);
        fprintf(stderr, "OUT_FILE can't opened\n");
        return EXIT_FAILURE;
    }
    numbers = fget_numbers(in, &ok);
    if (ok == false) {
        fclose(in);
        fprintf(out, "IN_FILE must have only digits");
        fclose(out);
        return EXIT_FAILURE;
    }
    if (numbers > 0) {
        int *it, n = numbers;
        int filtered;
        in_array_begin = calloc(numbers + 1, sizeof(int *));
        rewind(in);
        for (it = in_array_begin; n > 0; it++) {
            fscanf(in, "%d", it);
            --n;
        }
        in_array_end = it;
        if (argc == 4 && (*argv[3]) == 'f') {
            filtered = key(in_array_begin, it, &out_array_begin, &out_array_end);
        } else {
            out_array_begin = in_array_begin;
            out_array_end = in_array_end;
            filtered = numbers;
        }
        mysort(out_array_begin, filtered, sizeof(int), compare_int_fn);
        for (it = out_array_begin; it != out_array_end; ++it) {
            fprintf(out, "%d ", (*it));
        }

        free(in_array_begin);
        if (in_array_begin != out_array_begin) {
            free(out_array_begin);
        }
    } else {
        fprintf(stderr, "IN_FILE is empty\n");
        fprintf(out, "IN_FILE is empty");
        ret = EXIT_FAILURE;
    }

    fclose(in);
    fclose(out);
    return ret;
}

#endif
