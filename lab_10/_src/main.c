#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <main.h>

int comparator(const void *data, const void *find) {
    return strcmp(data, find);
}

struct Node *node_create(void *element) {
    struct Node *node = calloc(1, sizeof(struct Node));
    node->data = element;
    node->next = 0;
    return node;
}

struct Node *node_head(struct Node *root) {
    return root;
}

struct Node *node_prev(struct Node *root, struct Node *origin) {
    struct Node *it = root;
    struct Node *prev = 0;
    if (0 == it)
        return 0;
    while (0 != it) {
        if (origin == it)
            break;
        prev = it;
        it = it->next;
    }
    return prev;
}

struct Node *node_tail(struct Node *root, struct Node **prev) {
    struct Node *it = root;
    if (0 == it)
        return 0;
    if (prev)
        (*prev) = it;
    while (0 != it) {
        if (0 == it->next)
            break;
        if (prev)
            (*prev) = it;
        it = it->next;
    }
    return it;
}

struct Node *node_next(struct Node *root, ssize_t n) {
    struct Node *it = root;
    while (0 != it && n >= 0) {
        if (n == 0)
            return it;
        it = it->next;
        --n;
    }
    /*Если список двусвязный, можно переходить на предыдущие(при отрицательных значениях)*/
    return 0;
}

void node_append(struct Node **root, void *element) {
    struct Node *it;
    if (0 == root)
        return;
    it = node_create(element);
    if (0 == *root) {
        *root = it;
    } else {
        struct Node *tail = node_tail(*root, 0);
        tail->next = it;
    }
}

void node_destroy(struct Node **root, void (*destroy)(void *element)) {
    if (0 != root) {
        struct Node *it = *root;

        while (0 != it) {
            struct Node *tmp = it;
            it = it->next;
            (*destroy)(tmp->data);
            free(tmp);
        }
        *root = 0;
    }
}

void node_foreach(struct Node *root, void (*callback)(void *element, void *userdata), void *userdata) {
    struct Node *it = root;
    while (0 != it) {
        (*callback)(it->data, userdata);
        it = it->next;
    }
}

bool fread_struct(FILE *fd, int fields_count, void (*callback)(const char **fields, void *userdata), void *userdata) {
    char **fields = calloc(fields_count, sizeof(char *));
    char *p = 0;
    int allocated = 0;
    int pos = 0;
    int i = 0;

    while (!feof(fd)) {
        int ch = fgetc(fd);
        if ('\n' == ch || '\r' == ch || EOF == ch) {
            fields[i] = p;
            p = 0;
            i++;
            if (i >= fields_count) {
                (*callback)((const char **) fields, userdata);
                for (i = 0; i < fields_count; ++i) {
                    free(fields[i]);
                }
                i = 0;
            }
        } else {
            if (0 == p) {
                p = calloc(256, sizeof(char));
                allocated = 256;
                pos = 0;
            } else {
                ++pos;
                if (pos >= allocated) {
                    allocated += 256;
                    p = calloc(allocated, sizeof(char));
                }
            }
            p[pos] = (char) ch;
        }
    }
    free(fields);
    return true;
}

void string_clean(struct String *line) {
    if (0 != line) {
        memset(line->data, 0, line->allocated);
        line->len = 0;
    }
}

void string_append(struct String *s, int ch) {
    if (0 == s->data) {
        s->allocated = 256;
        s->data = calloc(s->allocated, sizeof(char));
        s->len = 0;
    } else if (s->len + 1 >= s->allocated) {
        s->allocated += 256;
        s->data = realloc(s->data, s->allocated);
    }
    s->data[s->len] = (char) ch;
    s->len++;
}

void string_read(FILE *fd, struct String *line) {
    int ch;

    string_clean(line);
    while ((ch = fgetc(fd)) != EOF && '\n' != ch) {
        string_append(line, ch);
    }
}

