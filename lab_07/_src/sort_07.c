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
    int *last_swapped_direct = main_end, *swapped_direct = last_swapped_direct;
    int *last_swapped_back = begin, *swapped_back = last_swapped_back;

    for (main_it = begin; main_it < main_end; main_it++) {
        if ( (((char *)main_it - (char *)begin) / element_size) % 2 == 0 ) {
            for (second_it = main_end - 1; second_it > last_swapped_back; second_it--) {
                if ((*compare_fn)(second_it - 1, second_it) > 0) {
                    swap(second_it, second_it - 1);
                    swapped_back = second_it;
                }
            }
            last_swapped_back = swapped_back;
        } else {
            for (second_it = begin; second_it < last_swapped_direct; second_it++) {
                if ((*compare_fn)(second_it, second_it + 1) > 0) {
                    swap(second_it, second_it + 1);
                    swapped_direct = second_it;
                }
            }
            last_swapped_direct = swapped_direct;
        }
    }
}
