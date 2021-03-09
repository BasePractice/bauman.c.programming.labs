#include <stdlib.h>
#include <fn_pop_front.h>

void* pop_front(struct Node **root) {
    if (0 != root && 0 != *root) {
        struct Node *c = (*root)->next;
        void *data = (*root)->data;
        if (0 == c) {
            *root = 0;
        } else {
            struct Node *t = *root;
            *root = c;
            free(t);
        }
        return data;
    }
    return 0;
}
