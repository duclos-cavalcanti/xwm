#ifndef __MAIN__H
#define __MAIN__H

#include <X11/Xlib.h>
#include <stdbool.h>

// Taken from DWM. Many thanks. https://git.suckless.org/dwm
#define MOD_CLEAN(mask) (mask & ~(LockMask) & \
        (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))


typedef union arg {
  const char** string; 
  const int i; 
  const void *data;
} arg_t;

typedef void(*callback_t)(const arg_t *arg);

typedef struct key_event {
  unsigned int mod; 
  KeySym keysym;
  callback_t callback;
  const arg_t arg;
} key_event_t;

typedef struct client {
    struct client *next, *prev;
    Window win;
    int x, y;
    unsigned int w, h;
    bool is_floating, is_fullscreen, is_focused, is_urgent, is_sticky;
} client_t;

typedef struct frame {
    struct frame *next;
    client_t *list;
    int size, cur;
} frame_t;

typedef struct workspace {
    frame_t *list;
    int size, cur;
} workspace_t;

typedef struct desktop {
    workspace_t ws[9];
    int cur;
} desktop_t;

typedef struct window_manager {
    Display* dpy;
    Window root;
    desktop_t desktop;
    int width, height;
    bool running;
} window_manager_t;

extern window_manager_t* wm;

#endif /* __MAIN__H */
