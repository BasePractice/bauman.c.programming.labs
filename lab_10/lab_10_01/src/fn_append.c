#include <stdlib.h>
#include <fn_pop_front.h>
#include <fn_append.h>

void append(struct Node **a, struct Node **b) {
    if (0 == b || 0 == *b)
        return;
    while (0 != *b) {
        node_append(a, pop_front(b));
    }
}
