#ifndef __MAIN__H
#define __MAIN__H

#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct config {
    unsigned int border_width;
    unsigned long border_color;
    unsigned long bg_color;
} config_t;

typedef enum layout {
    VERTICAL,
    HORIZONTAL,
    STACKED,
} layout_t;

typedef struct client {
    Window win;
    int x, y;
    unsigned int width, height;
    bool is_floating, is_fullscreen, is_focused, is_urgent, is_sticky;
} client_t;

typedef struct client_node {
    client_t* c;
    struct client_node* next;
} client_node_t;

typedef struct client_list {
    client_node_t* head;
} client_list_t;

typedef struct window_manager {
    Display* dpy;
    Window* root;
    client_list_t clients;
    int width, height;
    bool running, wm_found;
} window_manager_t;

#endif /* __MAIN__H */
