#ifndef BMAN_21_12_2020_MENU_H
#define BMAN_21_12_2020_MENU_H
#include <stdbool.h>
#include <main.h>

struct Menu {
    char *command;
    bool need_next_read;
    bool (*fn)(char *line, void *ctx);
};

void menu_register(struct Node **menu, char *command, bool need_next_read, bool (*fn)(char *line, void *ctx));
void menu_loop(struct Node *menu, void *ctx);
void menu_destroy(struct Node **menu);

#endif //BMAN_21_12_2020_MENU_H
