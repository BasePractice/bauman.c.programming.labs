#ifndef BMAN_21_12_2020_MAIN01_H
#define BMAN_21_12_2020_MAIN01_H
#include <stdio.h>
#include <stdbool.h>

struct Node {
    char   *data;
    struct Node *next;
};

int comparator(const void *data, const void *find);

void node_append(struct Node **root, void *element);
void node_destroy(struct Node **root, void (*destroy)(void *element));
void node_foreach(struct Node *root, void (*callback)(void *element, void *userdata), void *userdata);
struct Node *node_next(struct Node *root, ssize_t n);
struct Node *node_tail(struct Node *root, struct Node **prev);
struct Node *node_prev(struct Node *root, struct Node *origin);
struct Node *node_head(struct Node *root);
struct Node *node_create(void *element);

/** Данные полей очищаются после callback вызывающей функцией */
bool fread_struct(FILE *fd, int fields_count, void (*callback)(const char **fields, void *userdata), void *userdata);

struct String {
    char *data;
    int allocated;
    int len;
};

void string_clean(struct String *line);
void string_append(struct String *s, int ch);
void string_read(FILE *fd, struct String *line);

#endif //BMAN_21_12_2020_MAIN01_H
