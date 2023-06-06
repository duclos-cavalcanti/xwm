#ifndef __CLIENTS__H__H
#define __CLIENTS__H__H

#include "main.h"

client_list_t* new_list(void);
void insert_client(client_list_t* l, Window* win);
client_t* find_client(client_list_t* l, Window* win);

#endif /* __CLIENTS__H */
