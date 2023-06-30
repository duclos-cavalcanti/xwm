#include <stdio.h>

#include <X11/XF86keysym.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include "events.h"
#include "client.h"
#include "config.def.h"

// when a window is created, apply default settings
void create_notify(const XEvent* e) {

}

// when a window is destroyed, update internal state
void destroy_notify(const XEvent* e) {

}

// when a window requests to be mapped/shown on the screen, 
void map_request(const XEvent* e) {
    workspace_t *ws = &(wm->desktop.ws[wm->desktop.cur]);
    frame_t *fr = ws->cur;

    if (! (fr->list) ) {

    }

    add_client(fr, e->xmaprequest.window);

    GET_GEOMETRY(fr->list);

    move_client(fr->cur);
    map_client(fr->cur);
    focus_client(fr->cur);
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
    XConfigureRequestEvent *ev = &(e->xconfigurerequest);

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
    KeySym keysym = XkbKeycodeToKeysym(wm->dpy, e->xkey.keycode, 0, 0);
    for (unsigned int i = 0; i < sizeof(key_bindings)/sizeof(*key_bindings); i++) {
        key_event_t ke = key_bindings[i];
        if( ke.keysym == keysym && MOD_CLEAN(ke.mod) == MOD_CLEAN(e->xkey.state))
            ke.callback(&ke.arg);
    }

}

void key_release(const XEvent* e) {

}
