#include <string.h>
#include <memory.h>
#include <text.h>

void text_parse(const char *text, struct Node **root) {
    char part[PART_SIZE + 2] = {0};
    char *it = (char *)text;
    int c = 0;

    while (*it) {
        part[c++] = *it;
        if (c >= PART_SIZE) {
            node_append(root, strdup(part));
            memset(part, 0, sizeof(part));
            c = 0;
        }
        ++it;
    }

    if (c > 0) {
        node_append(root, strdup(part));
        memset(part, 0, sizeof(part));
    }
}

