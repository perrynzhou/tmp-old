/*************************************************************************
  > File Name: list.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 24 Nov 2019 10:53:08 AM CST
 ************************************************************************/

#include "cstl_list.h"
#include <stdio.h>
#include <stdlib.h>
list_node_t *list_node_create(void *value)
{
  list_node_t *node = NULL;
  if (value != NULL)
  {
    node = (list_node_t *)calloc(1, sizeof(list_node_t));
    if (node != NULL)
    {
      node->prev = node->next = NULL;
      node->value = value;
    }
  }
  return node;
}
inline void list_node_destroy(list_node_t *node)
{
  if (node != NULL)
  {
    node->prev = node->next = NULL;
    free(node);
    node = NULL;
  }
}
list_t *list_create()
{
  list_t *lt  = (list_t *)calloc(1, sizeof(list_t));
    if (lt != NULL)
    {
      lt->head = lt->tail = NULL;
      lt->size = 0;
    
  }
  return lt;
}
void list_set_callback(list_t *lt,cstl_list_node_value_free free,cstl_list_node_value_cmp cmp){
   if(lt!=NULL && free!=NULL && cmp!=NULL) {
     lt->cmp=cmp;
     lt->free=free;
   }
}
int list_insert(list_t *lt, list_node_t *node)
{
  if (lt != NULL)
  {
    if (lt->size == 0)
    {
      lt->head = lt->tail = node;
    }
    else
    {
      lt->tail->next = node;
      node->prev = lt->tail;
      lt->tail = node;
    }
    __sync_fetch_and_add(&lt->size, 1);
    return 0;
  }
  return -1;
}
int list_delete(list_t *lt, list_node_t *node)
{

  if (lt != NULL && lt->size > 0)
  {
    if (node->prev != NULL)
    {
      node->prev->next = node->next;
    }
    else
    {
      lt->head = node->next;
    }
    if (node->next != NULL)
    {
      node->next->prev = node->prev;
    }
    else
    {
      lt->tail = node->prev;
    }
    list_node_destroy(node);
    __sync_fetch_and_sub(&lt->size, 1);
  }
}
void list_destroy(list_t *lt)
{
  if (lt != NULL && lt->size > 0)
  {
    list_node_t *head = lt->head;
    list_node_t *tail = lt->tail;
    lt->size = 0;
    if (head != NULL)
    {
      while (head != tail)
      {
        list_node_t *next = head->next;
        list_node_t *prev = tail->prev;
        if(lt->free !=NULL) {
          lt->free(head->value);
          lt->free(tail->value);

        }
        list_node_destroy(head);
        list_node_destroy(tail);
        head = next;
        tail = prev;
        __sync_fetch_and_sub(&lt->size, 1);
      }
      if (lt->size > 0)
      {
         if(lt->free !=NULL) {
          lt->free(head->value);
        }
        list_node_destroy(head);
        __sync_fetch_and_sub(&lt->size, 1);
        head = tail = NULL;
      }
    }
    free(lt);
    lt = NULL;
  }
}