#include <stdlib.h>
#include <fn_pop_back.h>

void *pop_back(struct Node **root) {
    if (0 != root && 0 != *root) {
        struct Node *prev = 0;
        struct Node *tail = node_tail(*root, &prev);
        void *element;

        element = tail->data;
        if (*root == tail) {
            *root = 0;
        } else {
            prev->next = 0;
        }
        free(tail);
        return element;
    }
    return 0;
}
