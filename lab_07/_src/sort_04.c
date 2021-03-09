#include <main.h>
static inline void swap(int *d, int *s) {
    int v = *s;
    *s = *d;
    *d = v;
}

static int *binary_search(int *begin, int *end, int search, int (*compare_fn)(const void *, const void *)) {
    int *mid;
    if (begin == end || begin > end)
        return 0;
    mid = begin + ((((char *) end - (char *) begin) / sizeof(int)) / 2);
    if (*mid == search)
        return mid;
    if ((*compare_fn)(mid, &search) > 0)
        return binary_search(mid, end, search, compare_fn);
    return binary_search(begin, mid, search, compare_fn);
}

void mysort(void *begin, size_t elements, size_t element_size, int (*compare_fn)(const void *, const void *)) {
    int *end = (int *) ((char *) begin + (elements * element_size));
    int *main_it = begin;
    int *second_it = begin;

    begin = binary_search(begin, end, 9, compare_fn);
    for (main_it = begin; main_it < end - 1; main_it++) {
        for (second_it = main_it + 1; second_it < end; second_it++) {
            if ((*compare_fn)(main_it, second_it) > 0) {
                swap(second_it, main_it);
            }
        }
    }
}
