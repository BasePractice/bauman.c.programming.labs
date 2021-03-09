#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <main.h>
#include <menu.h>
#include <value.h>
#include <text.h>


/**FIXME: Не доделан до конца */
static void print_element(void *element, void *userdata) {
    if (0 != element) {
        fprintf(stdout, "%s ", (char *)element);
    }
}

static void destroy_element(void *element) {
    if (0 != element) {
        free(element);
    }
}

static void destroy_none(void *element) {
}

static bool menu_out(char *enter, void *userdata) {
    struct Node *root = 0;

    text_parse(enter, &root);
    node_foreach(root, print_element, 0);
    fprintf(stdout, "L\n");
    node_destroy(&root, destroy_element);
    return true;
}

static bool menu_cat(char *enter, void *userdata) {
    struct Node *src = 0;
    struct Node *dst = 0;
    struct Node *last;
    struct Node *it;
    int i = 0;
    size_t len;
    struct String line = {0, 0, 0};

    text_parse(enter, &dst);
    string_read(stdin, &line);
    last = node_tail(dst, 0);
    len = strlen(last->data);
    if (len < PART_SIZE) {
        int off = len;
        while (off < PART_SIZE && i < line.len) {
            last->data[off++] = line.data[i++];
        }
        last->data[off] = 0;
    }
    text_parse(line.data + i, &src);
    it = src;
    while (it) {
        node_append(&dst, strdup(it->data));
        it = it->next;
    }

    node_foreach(dst, print_element, 0);
    fprintf(stdout, "L\n");
    node_destroy(&dst, destroy_element);
    node_destroy(&src, destroy_element);
    return true;
}

int main(int argc, char **argv) {
    struct Node *menu = 0;

    menu_register(&menu, "out", true, menu_out);
    menu_register(&menu, "cat", true, menu_cat);
    menu_loop(menu, 0);
    menu_destroy(&menu);
    return EXIT_SUCCESS;
}
