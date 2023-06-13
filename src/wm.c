#include <stdio.h>
#include "main.h"

void create_notify(window_manager_t* wm, const XEvent* e) {

}

void configure_request(window_manager_t* wm, const XEvent* e) {
    XWindowChanges c;
    XConfigureRequestEvent *ev = &e->xconfigurerequest;

    c.x = ev->x;
    c.y = ev->y;
    c.width = ev->width;
    c.height = ev->height;
    c.border_width = ev->border_width;
    c.sibling = ev->above;
    c.stack_mode = ev->detail;

    XConfigureWindow(wm->dpy, 0, 0, &c); return;
}
