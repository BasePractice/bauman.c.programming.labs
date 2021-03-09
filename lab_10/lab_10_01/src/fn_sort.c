#include <fn_sort.h>

static void destroy_none(void *element) {

}

void sorted_insert(struct Node **root, struct Node *element, int (*comparator)(const void *, const void *)) {
    if (0 == root)
        return;
    if (0 == *root) {
        node_append(root, element->data);
    } else {
        struct Node *it = *root;
        struct Node *prev = it;
        int i = 0;

        while (0 != it) {
            int ret = (*comparator)(element->data, it->data);
            if (ret > 0 || 0 == ret) {
                struct Node *e = node_create(element->data);
                e->next = it;
                if (prev == *root && 0 == i) {
                    *root = e;
                } else {
                    prev->next = e;
                }
                break;
            }
            ++i;
            prev = it;
            it = it->next;
        }
    }
}

struct Node *sort(struct Node *root, int (*comparator)(const void *, const void *)) {
    struct Node *n = 0;
    struct Node *it = root;

    while (0 != it) {
        sorted_insert(&n, it, comparator);
        it = it->next;
    }
    node_destroy(&root, destroy_none);
    return n;
}
