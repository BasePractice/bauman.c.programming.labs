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
    fprintf(stdout, "%llu ", (long long) element);
}

static void destroy_none(void *element) {
}

static unsigned long next_prime(int n) {
    unsigned long i, j, c = 2;
    unsigned long last_prime;
    if (n == 0)
        return 2;
    if (n == 1)
        return 3;
    last_prime = 5;
    for (i = 5; c <= n; ++i) {
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                break;
            } else if (j + 1 > sqrt(i)) {
                last_prime = i;
                ++c;
            }
        }
    }
    return last_prime;
}

static void factor(unsigned long n, struct Node **num) {
    unsigned long last_prime;
    int c = 0, f = 0;

    while (n > 1) {
        last_prime = next_prime(c);
        if (0 == n % last_prime) {
            n /= last_prime;
            ++f;
            continue;
        } else {
            node_append(num, (void *) (long long) f);
            ++c;
            f = 0;
        }
    }
    if (f > 0) {
        node_append(num, (void *) (long long) f);
    }
}

/** 24 = 3 1L */
/** 1980 = 2 2 1 0 1L */
static bool menu_out(char *enter, void *userdata) {
    unsigned long n = strtol(enter, 0, 10);
    struct Node *num = 0;

    factor(n, &num);
    node_foreach(num, print_element, 0);
    fprintf(stdout, "L\n");
    node_destroy(&num, destroy_none);
    return true;
}

static bool menu_mul(char *enter, void *userdata) {
    struct String next = {0, 0, 0};
    long a = strtol(enter, 0, 10);
    long b, c;
    struct Node *num = 0;

    string_read(stdin, &next);
    if (next.len == 0) {
        fprintf(stderr, "Second mul not defined\n");
        free(next.data);
        return true;
    }
    b = strtol(next.data, 0, 10);
    c = a * b;

    factor(c, &num);
    node_foreach(num, print_element, 0);
    fprintf(stdout, "L\n");
    free(next.data);
    node_destroy(&num, destroy_none);
    return true;
}

static bool menu_sqr(char *enter, void *userdata) {
    long a = strtol(enter, 0, 10);
    struct Node *num = 0;

    factor(a * a, &num);
    node_foreach(num, print_element, 0);
    fprintf(stdout, "L\n");
    node_destroy(&num, destroy_none);
    return true;
}

static bool menu_div(char *enter, void *userdata) {
    struct String next = {0, 0, 0};
    long a = strtol(enter, 0, 10);
    long b, c;
    struct Node *num = 0;

    string_read(stdin, &next);
    if (next.len == 0) {
        fprintf(stdout, "Second mul not defined\n");
        fflush(stdout);
        free(next.data);
        return true;
    }
    b = strtol(next.data, 0, 10);
    if (b > a) {
        fprintf(stdout, "(NO OUT, ERROR)\n");
    } else {
        c = a /b;
        factor(c, &num);
        node_foreach(num, print_element, 0);
        fprintf(stdout, "L\n");
        node_destroy(&num, destroy_none);
    }
    fflush(stdout);
    free(next.data);
    return true;
}

int main(int argc, char **argv) {
    struct Node *menu = 0;

    menu_register(&menu, "out", true, menu_out);
    menu_register(&menu, "mul", true, menu_mul);
    menu_register(&menu, "sqr", true, menu_sqr);
    menu_register(&menu, "div", true, menu_div);
    menu_loop(menu, 0);
    menu_destroy(&menu);
    return EXIT_SUCCESS;
}
