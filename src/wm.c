#include <stdio.h>

#include "main.h"
#include "clients.h"

void create_notify(window_manager_t* wm, XEvent* e);
void configure_request(window_manager_t* wm, XEvent* e);
void configure_notify(window_manager_t* wm, XEvent* e);

static window_manager_t* wm_ = NULL;

// Many thanks. https://git.suckless.org/dwm
static void (*handler[LASTEvent]) (XEvent *) = {
	[CreateNotify] = create_notify,
	[ConfigureRequest] = configure_request,
	[ConfigureNotify] = configure_notify,
};

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

int process_event(window_manager_t* wm, XEvent* e) {
    wm_ = wm;
    if (handler(e))
        handler(e);
    return 0;
}
