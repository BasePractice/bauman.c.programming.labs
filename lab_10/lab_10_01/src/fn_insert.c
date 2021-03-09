#include <stdlib.h>
#include <fn_insert.h>

void insert(struct Node **root, struct Node *node, struct Node *before) {
    if (0 != root && 0 != *root) {
        struct Node *prev = node_prev(*root, before);
        if (0 == prev) {
            *root = node;
        } else {
            prev->next = node;
        }
        node->next = before;
    }
}
