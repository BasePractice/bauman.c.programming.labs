#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <main.h>
#include <menu.h>

static void item_destroy(void *element) {

}

void menu_loop(struct Node *menu, void *ctx) {
    bool running = true, exec = false;
    struct String line = {0, 0, 0};
    struct Node *it;
    if (0 == menu)
        return;
    while (running) {
        fprintf(stdout, "in >");
        fflush(stdout);

        exec = false;
        string_read(stdin, &line);
        it = menu;
        while (0 != it) {
            struct Menu *m = (struct Menu *) it->data;
            if (strcmp(line.data, m->command) == 0) {
                if (m->need_next_read)
                    string_read(stdin, &line);
                running = (*m->fn)(line.data, ctx);
                exec = true;
                break;
            }
            it = it->next;
        }

        if (false == exec) {
            fprintf(stdout, "Command \"%s\" not found.\n", line.data);
        }

    }
}

void menu_register(struct Node **menu, char *command, bool need_next_read, bool (*fn)(char *line, void *ctx)) {
    struct Menu *item = calloc(1, sizeof(struct Menu));
    item->command = command;
    item->need_next_read = need_next_read;
    item->fn = fn;
    node_append(menu, item);
}

void menu_destroy(struct Node **menu) {
    node_destroy(menu, item_destroy);
}

