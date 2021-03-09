#include <stdlib.h>
#include <memory.h>
#include <math.h>

void add_element(int **begin, int **end, int element) {
    if (*begin == 0) {
        *begin = malloc(sizeof(int));
        **begin = element;
        *end = *begin + 1;
    } else {
        int *temporary = *begin;
        size_t size = ((char *) (*end) - (char *) (*begin)) / sizeof(int);
        *begin = calloc(size + 1, sizeof(int));
        memcpy(*begin, temporary, size * sizeof(int));
        *end = *begin + size;
        **end = element;
        (*end)++;
        free(temporary);
    }
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst) {
    int *it;
    int c = 0;
    (*pb_dst) = 0;
    (*pe_dst) = 0;

    for (it = (int *) pb_src; it < pe_src; ++it, ++c) {
        if ((*it) < 0)
            break;
        add_element(pb_dst, pe_dst, (*it));
    }
    return c;
}
