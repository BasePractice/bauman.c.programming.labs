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
    int sum = 0;
    int c;

    (*pb_dst) = 0;
    (*pe_dst) = 0;

    for (it = (int *) pb_src, c = 0; it < pe_src; ++it) {
        if ((*it) > sum) {
            ++c;
            add_element(pb_dst, pe_dst, (*it));
        }
        sum += (*it);
    }
    return c;
}
