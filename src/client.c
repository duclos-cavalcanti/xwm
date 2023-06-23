#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void add_frame(frame_t* list) {

}

void add_client(frame_t *fr, Window win) {
    client_t* c = (client_t*) calloc(1, sizeof(client_t));
    client_t* list = fr->list;

    if (! (c) ) {
        fprintf(stderr, "Failed to allocate memory for client_t.\n");
        exit(EXIT_FAILURE);
    }

    c->win = win;
    c->next= NULL;
    c->prev= NULL;

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

    fr->size++;
    fr->cur = list;
}

void move_client(client_t* c) {
    XMoveResizeWindow(wm->dpy, 
                      c->win, 
                      c->x, 
                      c->y, 
                      c->w, 
                      c->h);
}

void map_client(client_t* c) {
    XMapWindow(wm->dpy, 
               c->win);
}

void focus_client(client_t* c) {
    XSetInputFocus(wm->dpy, c->win, RevertToParent, CurrentTime);
    c->is_focused = true;
}
