#ifndef BMAN_21_12_2020_VALUE_H
#define BMAN_21_12_2020_VALUE_H
#include <main.h>

struct ValuePolynomial {
    int n;
    int e;
};

struct ValuePolynomial *value_create(int n, int e);
inline char *value_skip_ws(char *it);
void pair_polynom_parse(const char *line, struct Node **values);
int uno_polynom_parse(const char *line, struct Node **values);

#endif //BMAN_21_12_2020_VALUE_H
