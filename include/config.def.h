#ifndef __CONFIG__H
#define __CONFIG__H

#include <X11/keysym.h>

#include "wm.h"

#define SUPER Mod4Mask

const char term[] = "xterm";

static key_event_t key_bindings[] = {
  { SUPER, XK_w, kill_win, {0} },
  { SUPER, XK_Return, command, {.string = term} },
};

#endif /* __CONFIG__H */

