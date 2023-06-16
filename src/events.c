#include <stdio.h>
#include "events.h"
#include "client.h"

// when a window is created, apply default settings
void create_notify(const XEvent* e) {

}

// when a window is destroyed, update internal state
void destroy_notify(const XEvent* e) {

}

// when a window requests to be mapped/shown on the screen, 
void map_request(const XEvent* e) {
    client_add(wm->clients, e->xmaprequest.window);
    client_get_geometry(wm, wm->clients->list, &(Status){0});

    client_place(wm, wm->clients->list);
    client_position(wm, wm->clients->list);
    client_map(wm, wm->clients->list);

    client_set_focus(wm, wm->clients->list);
}

// when a window is mapped/shown from the screen, 
// remove decorations and adjust layout
void map_notify(const XEvent* e) {

}

// when a window is unmapped/hidden from the screen, 
// remove decorations and adjust layout
void unmap_notify(const XEvent* e) {

}

// when a window's size, position or border configuration changes
// update internal representation of window and adjust layout if necessary
void configure_request(const XEvent* e) {
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

// when a window gains or loses focus
void focus_in(const XEvent* e) {

}

void focus_out(const XEvent* e) {

}

// when window property changes, such as title, icon or state
void property_notify(const XEvent* e) {

}

// when portion of a window becomes visible, this event is triggered
void expose(const XEvent* e) {

}

// mouse buttons are pressed or released within a window
// implement window dragging, resizing, etc
void button_press(const XEvent* e) {

}

void button_release(const XEvent* e) {

}

// keys are pressed or released within a window
// handle shortcuts, hot-keys and modes
void key_press(const XEvent* e) {

}

void key_release(const XEvent* e) {

}
