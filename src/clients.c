#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "clients.h"

#define IS_EMPTY(LIST) (LIST->head == NULL)

client_list_t* new_list(void) {
    client_list_t* ret = (client_list_t*) calloc(1, sizeof(client_list_t));
    if (!ret) {
        fprintf(stderr, "Creating window list failed!\n");
        exit(EXIT_FAILURE);
    }

    return ret;
}

window_t* new_client(Window* win) {
    client_t* ret = (client_t*) calloc(1, sizeof(client_t));
    if (!ret) {
        fprintf(stderr, "Creating client struct failed!\n");
        exit(EXIT_FAILURE);
    }

    ret->win = (*win);
    ret->x = 0;
    ret->y = 0;
    ret->width = 0;
    ret->height = 0;
    ret->is_floating = false;
    ret->is_fullscreen = false;
    ret->is_focused = false;
    ret->is_urgent = false;
    ret->is_sticky = false;
    return ret;
}

client_node_t* new_client_node(Window* win) {
    client_node_t* ret = (client_t*) calloc(1, sizeof(client_node_t));
    if (!ret) {
        fprintf(stderr, "Creating client node failed!\n");
        exit(EXIT_FAILURE);
    }

    ret->c = new_client(win);
    ret->next = NULL;
    return ret;
}

void insert_client(client_list_t* l, Window* win) {
    if (IS_EMPTY(l)) {
        l->head = new_client_node(win);
    } else {
        client_t* it;
        for (it = l->head; it->next; it=it->next){}
        it->next = new_client_node(win);
    }
    return;
}

client_t* find_client(client_list_t* l, Window* win) {
    if (IS_EMPTY(l)) {
        return NULL;
    } else {
        client_t* it;
        for (it=l->head; it; it=it->next)
            if (it->c->win == *win)
                return it;
        return NULL;
    }
}
