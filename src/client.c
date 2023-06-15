#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void client_add(client_list_t *c_list, Window win) {
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

    if (c_list->head) {
        client_t* tmp = c_list->head;
        c_list->head = c;
        c->next = tmp;
        tmp->prev = c;
    } else {
        c_list->head = c;
    }

    c_list->size++;
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
    if (wm->c_list->size == 1) {
        c->w = wm->width;
        c->h = wm->height;
    } else {

    }
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
    wm->cur = c;
}
