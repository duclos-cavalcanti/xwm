#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void client_add(client_list_t *clients, Window win) {
    client_t* c = (client_t*) calloc(1, sizeof(client_t));

    if (! (c) ) {
        fprintf(stderr, "Failed to allocate memory for client_t.\n");
        exit(EXIT_FAILURE);
    }

    c->win = win;
    c->is_sticky = false;
    c->is_floating = false;
    c->is_fullscreen = false;
    c->is_urgent = false;
    c->is_focused = false;

    if (clients->list) {
        client_t* tmp = clients->list;
        clients->list = c;
        c->next = tmp;
        tmp->prev = c;
    } else {
        clients->list = c;
    }

    clients->size++;
}

void client_get_geometry(window_manager_t *wm, client_t *c, Status *st) {
    *(st) = XGetGeometry(wm->dpy, 
                         c->win,
                         &(Window){0},
                         &c->x, 
                         &c->y, 
                         &c->w, 
                         &c->h,
                         &(unsigned int){0},
                         &(unsigned int){0});
}

void client_place(window_manager_t* wm, client_t* c) {

}

void client_position(window_manager_t* wm, client_t* c) {
    XMoveResizeWindow(wm->dpy, 
                      c->win, 
                      c->x, 
                      c->y, 
                      c->w, 
                      c->h);
}

void client_map(window_manager_t* wm, client_t* c) {
    XMapWindow(wm->dpy, 
               c->win);
}

void client_set_focus(window_manager_t*wm, client_t* c) {
    XSetInputFocus(wm->dpy, c->win, RevertToParent, CurrentTime);
    c->is_focused = true;
    wm->clients->cur = c;
}
