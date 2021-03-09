#include <stdlib.h>
#include <ctype.h>
#include <value.h>

struct ValuePolynomial *value_create(int n, int e) {
    struct ValuePolynomial *p = calloc(1, sizeof(struct ValuePolynomial));
    p->n = n;
    p->e = e;
    return p;
}

inline char *value_skip_ws(char *it) {
    while (*it && isspace((int)(*it))) {
        ++it;
    }
    return it;
}

void pair_polynom_parse(const char *line, struct Node **values) {
    int state = 0, n = 0, e = 0;
    char *it = (char *)line;
    char *number_begin;

    number_begin = it = value_skip_ws(it);
    while ((*it)) {
        switch (state) {
            case 0: {
                if (!isdigit((int)(*it))) {
                    state = 1;
                    (*it) = 0;
                    n = strtol(number_begin, 0, 10);
                    number_begin = it = value_skip_ws(it + 1);
                    continue;
                }
                break;
            }
            case 1: {
                if (!isdigit((int)(*it))) {
                    state = 2;
                    (*it) = 0;
                    e = strtol(number_begin, 0, 10);
                    number_begin = it = value_skip_ws(it + 1);
                    continue;
                }
                break;
            }
            default:
            case 2: {
                node_append(values, value_create(n, e));
                state = 0;
                e = -1;
                n = -1;
                continue;
            }
        }
        ++it;
    }

    if (n > 0) {
        if (e < 0 && 0 != (*number_begin) ) {
            e = strtol(number_begin, 0, 10);
        }
        node_append(values, value_create(n, e));
        n = -1;
        e = -1;
    }

}

int uno_polynom_parse(const char *line, struct Node **values) {
    char *it = (char *)line;
    char *number_begin;
    int n;
    int c = 0;

    number_begin = it = value_skip_ws(it);
    while ((*it)) {
        if (!isdigit((int)(*it))) {
            (*it) = 0;
            n = strtol(number_begin, 0, 10);
            ++c;
            node_append(values, (void *)(long long)n);
            number_begin = it = value_skip_ws(it + 1);
            continue;
        }
        ++it;
    }

    if (0 != (*number_begin)) {
        n = strtol(number_begin, 0, 10);
        ++c;
        node_append(values, (void *)(long long)n);
    }
    return c;
}
