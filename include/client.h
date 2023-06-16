#ifndef __CLIENT__H
#define __CLIENT__H

#include "main.h"

void client_add(client_list_t *list, Window win);
void client_get_geometry(window_manager_t *wm, client_t *c, Status *st);
void client_place(window_manager_t* wm, client_t* c);
void client_position(window_manager_t* wm, client_t* c);
void client_map(window_manager_t* wm, client_t* c);
void client_set_focus(window_manager_t*wm, client_t* c);

#endif /* __CLIENT__H */
