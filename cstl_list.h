/*************************************************************************
  > File Name: cstl_list.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 24 Nov 2019 10:52:54 AM CST
 ************************************************************************/

#ifndef _CSTL_LIST_H
#define _CSTL_LIST_H
#include "cstl_def.h"
list_node_t *list_node_create(void *value);
void list_node_destroy(list_node_t *node);
list_t *list_create(cstl_list_node_value_cmp cmp);
int list_insert(list_t *lt,list_node_t *node);
int list_delete(list_t *lt,list_node_t *node);
void list_destroy(list_t *lt);
#endif
