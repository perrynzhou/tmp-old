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
typedef uint64_t  (*hash_fn)(const void *data,size_t len);
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
//that as list_node value
typedef struct cstl_hashtable_entry_t
{
  void *data;
  uint64_t  timestamp;
} hashtable_entry_t;
typedef struct ctl_hashtable_t
{
  vector_t tables;
  uint32_t max_bucket;
  uint32_t link_limit;//0 is unlimte;>0 is limite hash link node
} hashtable_t;
typedef struct cstl_bloom_filter_t {
  uint64_t  max_hash;
  vector_t  fn;
  uint8_t   *data;
}bloom_filter_t;
#endif
