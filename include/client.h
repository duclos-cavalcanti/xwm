#ifndef __CLIENT__H
#define __CLIENT__H

#include "main.h"

#define GET_GEOMETRY(c) XGetGeometry(wm->dpy, c->win, &(Window){0}, &c->x, &c->y, &c->w, &c->h, &(unsigned int){0}, &(unsigned int){0})

void add_frame(frame_t *list);
void add_client(frame_t *fr, Window win);
void get_client_geometry(client_t *c, Status *st);
void move_client(client_t* c);
void map_client(client_t* c);
void focus_client(client_t* c);

#endif /* __CLIENT__H */
