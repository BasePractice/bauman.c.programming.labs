#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <main.h>

void list_append(struct List *list, void *element) {
    if (0 == list)
        return;
    list_insert(list, list->size, element);
}

void list_insert(struct List *list, size_t index, void *element) {
    if (0 == list)
        return;
    if (0 == list->elements) {
        list->elements = calloc(1, sizeof(void *));
        list->elements[0] = element;
        list->size = 1;
    } else if (index <= list->size) {
        ssize_t it;

        list->size++;
        list->elements = realloc(list->elements, list->size * sizeof(void *));
        for (it = list->size - 1; it > index; --it) {
            list->elements[it] = list->elements[it - 1];
        }
        list->elements[index] = element;
    }
}

ssize_t binary_search(struct List *list, size_t start, size_t end, void *search, enum BinarySearchSide *side,
                      int (*compare_fn)(void *a, void *b, void *userdata), void *userdata) {
    size_t mid = 0;
    int result;
    if (0 == list || 0 == list->elements || 0 == list->size) {
        (*side) = EMPTY;
        return 0;
    }
    if (0 == end - start) {
        mid = start;
    } else if ((end - start) % 2 == 0) {
        mid = start + ((end - start) / 2);
    } else {
        mid = start + ((end - start) / 2);
        result = (*compare_fn)(list->elements[mid], search, userdata);
        if (0 == result) {
            (*side) = FOUND;
            return mid;
        }
        if (result > 0) {
            (*side) = RIGHT;
            return binary_search(list, mid + 1, end, search, side, compare_fn, userdata);
        }
        (*side) = LEFT;
        return binary_search(list, start, mid, search, side, compare_fn, userdata);
    }
    result = (*compare_fn)(list->elements[mid], search, userdata);
    if (0 == result) {
        (*side) = FOUND;
        return mid;
    }
    if (result > 0) {
        (*side) = RIGHT;
        if (start == mid) {
            return mid;
        }
        return binary_search(list, mid + 1, end, search, side, compare_fn, userdata);
    }
    (*side) = LEFT;
    if (start == mid) {
        return mid;
    }
    return binary_search(list, start, mid - 1, search, side, compare_fn, userdata);

}

void list_append_sort(struct List *list, void *element, int (*compare_fn)(void *a, void *b, void *userdata),
                      void *userdata) {
    enum BinarySearchSide side = EMPTY;
    ssize_t i = binary_search(list, 0, list->size - 1, element, &side, compare_fn, userdata);

    switch (side) {
        case NOT_FOUND: {
            list_append(list, element);
            break;
        }
        case FOUND:
        case LEFT: {
            list_insert(list, i, element);
            break;
        }
        case RIGHT: {
            list_insert(list, i + 1, element);
            break;
        }
        case EMPTY:
        default: {
            list_append(list, element);
            break;
        }
    }
}

/** Можно переиспользовать list_foreach */
void list_destroy(struct List *list, void (*destroy)(void *element)) {
    if (0 != list && 0 != list->elements) {
        size_t i;

        for (i = 0; i < list->size; ++i) {
            if (0 != list->elements[i]) {
                (*destroy)(list->elements[i]);
            }
        }
        free(list->elements);
        list->elements = 0;
        list->size = 0;
    }
}

void list_foreach(struct List *list, void (*callback)(void *element, void *userdata), void *userdata) {
    if (0 != list && 0 != list->elements) {
        size_t i;

        for (i = 0; i < list->size; ++i) {
            if (0 != list->elements[i]) {
                (*callback)(list->elements[i], userdata);
            }
        }
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