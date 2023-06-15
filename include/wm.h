#ifndef __WM__H
#define __WM__H

#include "main.h"

void create_notify(window_manager_t* wm, const XEvent* e);
void configure_request(window_manager_t* wm, const XEvent* e);
void map_request(window_manager_t* wm, const XEvent* e);

#endif /* __WM__H */
