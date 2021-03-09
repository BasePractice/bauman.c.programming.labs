#ifndef BMAN_21_12_2020_FN_FIND_H
#define BMAN_21_12_2020_FN_FIND_H

#include <main.h>

struct Node *find(struct Node *root, const void *data, int (*comparator)(const void *, const void *));

#endif //BMAN_21_12_2020_FN_FIND_H
