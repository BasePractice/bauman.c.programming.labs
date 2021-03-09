#include <main.h>
#include <fn_find.h>

struct Node *find(struct Node *root, const void *data, int (*comparator)(const void *, const void *)) {
    struct Node *it = root;
    while (0 != it) {
        if (0 == (*comparator)(it->data, data))
            return it;
        it = it->next;
    }
    return 0;
}
