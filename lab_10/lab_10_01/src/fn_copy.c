#include <main.h>
#include <fn_copy.h>

int copy(struct Node *root, struct Node **cpy) {
    struct Node *it = root;

    while (0 != it) {
        node_append(cpy, it->data);
        it = it->next;
    }
    return 0;
}
