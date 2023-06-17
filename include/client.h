#ifndef __CLIENT__H
#define __CLIENT__H

#include "main.h"

void add_frame(frame_t *list);

void add_client(client_t *list, Window win);
void get_client_geometry(window_manager_t *wm, client_t *c, Status *st);
void move_client(window_manager_t* wm, client_t* c);
void map_client(window_manager_t* wm, client_t* c);
void focus_client(window_manager_t*wm, client_t* c);

#endif /* __CLIENT__H */
