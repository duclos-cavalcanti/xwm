#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void add_frame() {

}

void add_client(client_t *list, Window win) {
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

    if (list) {
        client_t* tmp = list;
        list = c;
        c->next = tmp;
        tmp->prev = c;
    } else {
        list = c;
    }

    clients->size++;
}

void get_client_geometry(window_manager_t *wm, client_t *c, Status *st) {
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

void move_client(window_manager_t* wm, client_t* c) {
    XMoveResizeWindow(wm->dpy, 
                      c->win, 
                      c->x, 
                      c->y, 
                      c->w, 
                      c->h);
}

void map_client(window_manager_t* wm, client_t* c) {
    XMapWindow(wm->dpy, 
               c->win);
}

void focus_client(window_manager_t*wm, client_t* c) {
    XSetInputFocus(wm->dpy, c->win, RevertToParent, CurrentTime);
    c->is_focused = true;
}
