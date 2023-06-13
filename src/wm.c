#include <stdio.h>
#include "main.h"


void create_notify(const XEvent* e) {}

void configure_request(const XEvent* e) {
    wnode_t* wn;
    XWindowChanges c;
    XConfigureRequestEvent *ev = &e->xconfigurerequest;

    if ((wn = find_window(wm_->clients, ev->window))) {
        window_t* w = wn->w;
    } else {
        c.x = ev->x;
        c.y = ev->y;
        c.width = ev->width;
        c.height = ev->height;
        c.border_width = ev->border_width;
        c.sibling = ev->above;
        c.stack_mode = ev->detail;
    }

    XConfigureWindow(wm_->dpy, e->window, e->value_mask, &c);
    return;
}
