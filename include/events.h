#ifndef __EVENTS__H
#define __EVENTS__H

#include "main.h"

void create_notify(const XEvent* e);
void configure_request(const XEvent* e);

void map_notify(const XEvent* e);
void map_request(const XEvent* e);

void key_press(const XEvent* e);

#endif /* __EVENTS__H */
