#include <fn_pop_back.h>
#include <fn_reverse.h>

struct Node *reverse(struct Node *root) {
    struct Node *n = 0;

    while (root) {
        node_append(&n, pop_back(&root));
    }
    return n;
}
