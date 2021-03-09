#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <main.h>
#include <menu.h>
#include <value.h>

/**
 * В примерах к задаче 2.2 ошибка, перед выражением всегда стоит 4. Из-за этого результаты не совпадают с эталонными.
 * Есть предположение что 4 указывает на количество элементов в списке, но в задании про это ничего не указано.
 * Исходя из вышеописанного, количество элементов рассчитывается при разборе строки.
 */

static void print_element(void *element, void *userdata) {
    fprintf(stdout, "%llu ", (long long) element);
}

static void destroy_none(void *element) {
}

/** В примере ошибка для 4 4 2 0 6 */
static bool menu_val(char *enter, void *userdata) {
    struct String pn = {0, 0, 0};
    struct Node *polynomial = 0;
    struct Node *v;
    int a;
    int c;
    double sum;

    c = uno_polynom_parse(enter, &polynomial);
    if (0 == polynomial) {
        fprintf(stderr, "Polynomial not defined\n");
        return false;
    }
    string_read(stdin, &pn);
    if (0 == pn.len) {
        fprintf(stderr, "X not defined\n");
        free(pn.data);
        return false;
    }
    a = strtol(pn.data, 0, 10);
    v = polynomial;
    sum = 0;
    while (v && c) {
        int e = c - 1;
        sum += pow(a, e) * (double) (long long) v->data;
        v = v->next;
        --c;
    }
    fprintf(stdout, "out< %f\n", sum);
    free(pn.data);
    node_destroy(&polynomial, destroy_none);
    return true;
}

/** В примере ошибка для 4 4 2 0 6 */
static bool menu_ddx(char *enter, void *userdata) {
    struct Node *polynomial = 0;
    struct Node *v;
    int c;

    c = uno_polynom_parse(enter, &polynomial);
    if (0 == polynomial) {
        fprintf(stderr, "Polynomial not defined\n");
        return false;
    }
    v = polynomial;
    while (v && c) {
        int e = c - 1;
        int n = (int) (long long) v->data;

        if (e > 0) {
            int nn = n * e;
            fprintf(stdout, "%d ", nn);
        }
        v = v->next;
        --c;
    }
    fprintf(stdout, "L\n");
    node_destroy(&polynomial, destroy_none);
    return true;
}

static bool menu_sum(char *enter, void *userdata) {
    struct Context *ctx = (struct Context *) userdata;
    return true;
}

/** В примере ошибка для 4 4 2 0 6 */
static bool menu_dvd(char *enter, void *userdata) {
    struct Context *ctx = (struct Context *) userdata;
    struct Node *polynomial = 0;
    struct Node *even = 0;
    struct Node *odd = 0;
    struct Node *v;
    int c;

    c = uno_polynom_parse(enter, &polynomial);
    if (0 == polynomial) {
        fprintf(stderr, "Polynomial not defined\n");
        return false;
    }
    v = polynomial;
    while (v && c) {
        int e = c - 1;
        int n = (int) (long long) v->data;

        if (0 == e) {
            node_append(&even, (void *) (long long) n);
        } else if (e % 2 == 0) {
            node_append(&even, (void *) (long long) n);
        } else {
            node_append(&odd, (void *) (long long) n);
        }
        v = v->next;
        --c;
    }
    node_foreach(even, print_element, 0);
    fprintf(stdout, "L\n");
    node_foreach(odd, print_element, 0);
    fprintf(stdout, "L\n");
    node_destroy(&polynomial, destroy_none);
    node_destroy(&even, destroy_none);
    node_destroy(&odd, destroy_none);
    return true;
}

int main(int argc, char **argv) {
    struct Node *menu = 0;

    menu_register(&menu, "val", true, menu_val);
    menu_register(&menu, "ddx", true, menu_ddx);
    menu_register(&menu, "sum", true, menu_sum);
    menu_register(&menu, "dvd", true, menu_dvd);
    menu_loop(menu, 0);
    menu_destroy(&menu);
    return EXIT_SUCCESS;
}
