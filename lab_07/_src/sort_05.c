#include <main.h>

static inline void swap(int *d, int *s) {
    int v = *s;
    *s = *d;
    *d = v;
}

void mysort(void *begin, size_t elements, size_t element_size, int (*compare_fn)(const void *, const void *)) {
    int *end = (int *) ((char *) begin + (elements * element_size));
    int *main_it = begin, *main_end = end - 1;
    int *second_it = begin;
    int *last_swapped = main_end, *swapped = last_swapped;

    for (main_it = begin; main_it < main_end; main_it++) {
        for (second_it = begin; second_it < last_swapped; second_it++) {
            if ((*compare_fn)(second_it, second_it + 1) > 0) {
                swap(second_it, second_it + 1);
                swapped = second_it;
            }
        }
        last_swapped = swapped;
    }
}