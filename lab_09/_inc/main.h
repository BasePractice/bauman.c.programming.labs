#ifndef BMAN_21_12_2020_MAIN01_H
#define BMAN_21_12_2020_MAIN_H
#include <stdio.h>
#include <stdbool.h>

struct List {
    void   **elements;
    size_t  size;
};

enum BinarySearchSide {
    FOUND, LEFT, RIGHT, EMPTY, NOT_FOUND
};

void list_append(struct List *list, void *element);
void list_insert(struct List *list, size_t index, void *element);
void list_append_sort(struct List *list, void *element, int (*compare_fn)(void *a, void *b, void *userdata), void *userdata);
void list_destroy(struct List *list, void (*destroy)(void *element));
void list_foreach(struct List *list, void (*callback)(void *element, void *userdata), void *userdata);
ssize_t binary_search(struct List *list, size_t start, size_t end, void *search, enum BinarySearchSide *side,
                     int (*compare_fn)(void *a, void *b, void *userdata), void *userdata);

/** Данные полей очищаются после callback вызывающей функцией */
bool fread_struct(FILE *fd, int fields_count, void (*callback)(const char **fields, void *userdata), void *userdata);

#endif //BMAN_21_12_2020_MAIN01_H
