#include <stdlib.h>
#include <memory.h>
#include <math.h>

void calc_limits(const int *begin, const int *end, int **p_maximum, int **p_minimum) {
    int *it = (int *)begin;
    int maximum = (*it), minimum = (*it);

    (*p_maximum) = it;
    (*p_minimum) = it;
    while (it <= end) {
        if ((*it) > maximum) {
            maximum = (*it);
            (*p_maximum) = it;
        }
        if ((*it) < minimum) {
            minimum = (*it);
            (*p_minimum) = it;
        }
        ++it;
    }
}

void add_element(int **begin, int **end, int element) {
    if (*begin == 0) {
        *begin = malloc(sizeof(int));
        **begin = element;
        *end = *begin + 1;
    } else {
        int *temporary = *begin;
        size_t size = ((char *)(*end) - (char *)(*begin)) / sizeof(int);
        *begin = calloc(size + 1, sizeof(int));
        memcpy(*begin, temporary, size * sizeof(int));
        *end = *begin + size;
        **end = element;
        (*end)++;
        free(temporary);
    }
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst) {
    int *maximum = (int *)pe_src, *minimum = (int *)pb_src;
    int *it;
    int c = 0;
    (*pb_dst) = 0;
    (*pe_dst) = 0;

    calc_limits(pb_src, pe_src, &maximum, &minimum);
    if (minimum == maximum)
        return 0;
    if (minimum > maximum) {
        int *t = maximum;
        maximum = minimum;
        minimum = t;
    }
    for (it = minimum; it <= maximum; ++it, ++c) {
        add_element(pb_dst, pe_dst, (*it));
    }
    return c;
}
