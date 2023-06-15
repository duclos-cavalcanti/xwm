#ifndef __MAIN__H
#define __MAIN__H

#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct client {
    struct client *next, *prev;
    Window win;
    int x, y;
    unsigned int w, h;
    bool is_floating, is_fullscreen, is_focused, is_urgent, is_sticky;
} client_t;

typedef struct client_list {
    client_t* head;
    int size;
} client_list_t;

typedef struct window_manager {
    Display* dpy;
    Window root;
    client_list_t *c_list;
    client_t* cur;
    int screen;
    int width, height;
    bool running;
} window_manager_t;

#endif /* __MAIN__H */
