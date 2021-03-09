#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <main.h>
#include <menu.h>
#include <value.h>

static void print_element(void *element, void *userdata) {
    struct ValuePolynomial *polynomial = (struct ValuePolynomial *)element;
    if (0 != polynomial) {
        fprintf(stdout, "%d %d ", polynomial->n, polynomial->e);
    }
}

static void destroy_element(void *element) {
    if (0 != element) {
        free(element);
    }
}

static void destroy_none(void *element) {
}

static bool menu_val(char *enter, void *userdata) {
    struct String pn = {0, 0, 0};
    struct Node *polynomial = 0;
    struct Node *v;
    int a;
    double sum;

    pair_polynom_parse(enter, &polynomial);
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
    while (v) {
        sum += pow(a, ((struct ValuePolynomial *)v->data)->e) * ((struct ValuePolynomial *)v->data)->n;
        v = v->next;
    }
    fprintf(stdout, "out< %f\n", sum);
    free(pn.data);
    node_destroy(&polynomial, destroy_element);
    return true;
}

static bool menu_ddx(char *enter, void *userdata) {
    struct Node *polynomial = 0;
    struct Node *v;

    pair_polynom_parse(enter, &polynomial);
    if (0 == polynomial) {
        fprintf(stderr, "Polynomial not defined\n");
        return false;
    }
    v = polynomial;
    while (v) {
        int e = ((struct ValuePolynomial *)v->data)->e;
        int n = ((struct ValuePolynomial *)v->data)->n;

        if (e > 0) {
            int ne = e - 1;
            int nn = n * e;
            fprintf(stdout, "%d %d ", nn, ne);
        }
        v = v->next;
    }
    fprintf(stdout, "L\n");
    node_destroy(&polynomial, destroy_element);
    return true;
}

static bool menu_sum(char *enter, void *userdata) {
    struct Context *ctx = (struct Context *)userdata;
    return true;
}

static bool menu_dvd(char *enter, void *userdata) {
    struct Context *ctx = (struct Context *)userdata;
    struct Node *polynomial = 0;
    struct Node *even = 0;
    struct Node *odd = 0;
    struct Node *v;

    pair_polynom_parse(enter, &polynomial);
    if (0 == polynomial) {
        fprintf(stderr, "Polynomial not defined\n");
        return false;
    }
    v = polynomial;
    while (v) {
        int e = ((struct ValuePolynomial *)v->data)->e;
        int n = ((struct ValuePolynomial *)v->data)->n;

        if (0 == e) {
            node_append(&even, value_create(n, e));
        } else if (e % 2 == 0) {
            node_append(&even, value_create(n, e));
        } else {
            node_append(&odd, value_create(n, e));
        }
        v = v->next;
    }
    node_foreach(even, print_element, 0);
    fprintf(stdout, "L\n");
    node_foreach(odd, print_element, 0);
    fprintf(stdout, "L\n");
    node_destroy(&polynomial, destroy_element);
    node_destroy(&even, destroy_element);
    node_destroy(&odd, destroy_element);
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
