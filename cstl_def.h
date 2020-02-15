/*************************************************************************
  > File Name: cstl_def.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sat 15 Feb 2020 10:11:23 AM CST
 ************************************************************************/

#ifndef _CSTL_DEF_H
#define _CSTL_DEF_H
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#define CSTL_STRING_INTERNAL_LENGTH (16)
typedef struct cstl_string_t
{
  union {
    char buffer[CSTL_STRING_INTERNAL_LENGTH];
    char *ptr;
  } data;
  size_t length;
} string_t;

typedef int (*cstl_list_node_value_cmp)(void *, void *);

typedef struct cstl_list_node_t
{
  struct cstl_list_node_t *next;
  struct cstl_list_node_t *prev;
  void *value;
} list_node_t;
typedef struct cstl_list_t
{
  list_node_t *head;
  list_node_t *tail;
  size_t size;
  cstl_list_node_value_cmp cmp;
} list_t;
typedef struct cstl_netsocket_t
{
  int port;
  char *addr;
  int backlog;
  struct ev_loop *loop;
  int sock;
  void *ctx;
} netsocket_t;
typedef struct cstl_vector_t
{
  uint64_t size;
  uint64_t cap;
  void **tables;
  pthread_mutex_t lock;
} vector_t;
#endif