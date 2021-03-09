#include <stdlib.h>
#include <fn_find.h>
#include <fn_remove_duplicates.h>

void remove_duplicates(struct Node **root, int (*comparator)(const void *, const void *)) {
    if (0 == root || *root == 0)
        return;
    struct Node *it = *root;
    while (0 != it) {
        struct Node *found;
        struct Node *second;

        if (0 == it->next)
            break;
        second = it->next;
        while ((found = find(second, it->data, comparator)) != 0) {
            struct Node *prev = node_prev(*root, found);
            if (0 == prev)
                break;
            prev->next = found->next;
            second = found->next;
            free(found);
        }
        it = it->next;
    }
}
