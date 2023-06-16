#ifndef __MAIN__H
#define __MAIN__H

#include <X11/Xlib.h>
#include <stdbool.h>

typedef union arg {
  const char** command; 
  const int i; 
  const void *data;
} arg_t;

typedef struct key_event {
  unsigned int mod; 
  KeySym keysym;
  void(*function)(const arg_t *arg);
  const arg_t arg;
} key_event_t;

typedef struct client {
    struct client *next, *prev;
    Window win;
    int x, y;
    unsigned int w, h;
    bool is_floating, is_fullscreen, is_focused, is_urgent, is_sticky;
} client_t;

typedef struct client_list {
    client_t* list;
    client_t* cur;
    int size;
} client_list_t;

typedef struct window_manager {
    Display* dpy;
    Window root;
    client_list_t *clients;
    int screen;
    int width, height;
    bool running;
} window_manager_t;

extern window_manager_t* wm;

#endif /* __MAIN__H */
