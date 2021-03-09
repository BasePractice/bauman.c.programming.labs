#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <math.h>

/** Возвращаем 0 если все скопировалось удачно и > 0 необходимое количество элементов */
int key(const int *pb_src, const int *pe_src, int *pb_dst, int size) {
    int *it;
    int *end_search = (int *)pe_src;
    int c = 0;
    bool ge = false;

    (*pb_dst) = 0;

    for (it = (int *) pb_src; it < end_search; ++it, c++) {
        if ((*it) < 0)
            break;
        if (c < size) {
            pb_dst[c] = (*it);
        } else {
            ge = true;
        }
    }
    return ge ? c : 0;
}
