#include <main.h>

static inline void swap(int *d, int *s) {
    int v = *s;
    *s = *d;
    *d = v;
}

void mysort(void *begin, size_t elements, size_t element_size, int (*compare_fn)(const void *, const void *)) {
    int *end = (int *) ((char *) begin + (elements * element_size));
    int *main_it = begin;
    int *second_it = begin;

    for (main_it = begin; main_it < end - 1; main_it++) {
        for (second_it = main_it + 1; second_it < end; second_it++) {
            if ((*compare_fn)(main_it, second_it) > 0) {
                swap(second_it, main_it);
            }
        }
    }
}

