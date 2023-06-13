#ifndef __MAIN__H
#define __MAIN__H

#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct client {
    Window win;
    int x, y;
    unsigned int width, height;
    bool is_floating, is_fullscreen, is_focused, is_urgent, is_sticky;
} client_t;

typedef struct window_manager {
    Display* dpy;
    Window* root;
    int screen;
    int width, height;
    bool running;
} window_manager_t;

#endif /* __MAIN__H */
