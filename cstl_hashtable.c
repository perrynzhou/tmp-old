/*************************************************************************
  > File Name: cstl_hashtable.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sat 15 Feb 2020 08:33:13 PM CST
 ************************************************************************/
#include "cstl_def.h"
#include "cstl_hashtable.h"
#include "cstl_vector.h"
#include "cstl_hash.h"
#include "cstl_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
static inline uint64_t hashtable_fetch_timestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (uint64_t)(tv.tv_sec * 1000000 + tv.tv_usec);
}
static inline uint64_t hashtable_jump_consistent(uint64_t key, uint64_t num_buckets)
{

  int64_t b = -1, j = 0;
  uint64_t value = 0;
  while (j < num_buckets)
  {
    b = j;
    key = key * 2862933555777941757ULL + 1;
    j = (b + 1) * ((double)(1LL << 31) / (double)((key >> 33) + 1));
  }
  value = (b < 0) ? (~b + 1) : b;
  return value;
}

int hashtable_init(hashtable_t *ht, uint32_t max_buckets,cstl_cmp_fn fn)
{
  if (ht != NULL&&fn!=NULL)
  {
    vector_init(&ht->tables, max_buckets);
    return 0;
  }
  return -1;
}
hashtable_t *hashtable_create(uint32_t max_buckets, cstl_cmp_fn fn)
{
  hashtable_t *ht = (hashtable_t *)calloc(1, sizeof(hashtable_t));
  if (ht != NULL)
  {
    if (hashtable_init(ht, max_buckets,fn) != 0)
    {
      free(ht);
      ht = NULL;
    }
  }
  return ht;
}

//return data insert timestamp,that as unique id for data
int hashtable_insert(hashtable_t *ht, void *data,uint64_t hash)
{
  uint64_t index = hashtable_jump_consistent(hash, ht->max_bucket);
  list_t *lt = (list_t *)vector_at(&ht->tables, index);
  if (lt == NULL)
  {
    lt = list_create();
    vector_push_back(&ht->tables, lt);
  }
  list_node_t *node = list_node_create(data);
  if(node!=NULL) {
     list_insert(lt, node);
     return 0;
  }
  list_node_destroy(node);
  return -1;
}
static void *hashtable_search_node(hashtable_t *ht, void *key,uint64_t hash)
{
  list_node_t *result = NULL;
  if (ht != NULL)
  {
    uint64_t index = hashtable_jump_consistent(hash, ht->max_bucket);
    list_t *lt = (list_t *)vector_at(&ht->tables, index);
    if (lt != NULL)
    {
      list_node_t *cur = lt->head;
      while (cur != NULL)
      {
        list_node_t *next = cur->next;
        if (ht->cmp(cur->value,key) ==0)
        {
          result = cur;
          break;
        }
      }
    }
  }
  return result;
}
int hashtable_delete(hashtable_t *ht, void *key,uint64_t hash)
{
  list_node_t *node = (list_node_t *)hashtable_search_node(ht, key,hash);
  if (node != NULL)
  {
    pthread_mutex_lock(&ht->lock);
    uint64_t index = hashtable_jump_consistent(hash, ht->max_bucket);
    list_t *lt = (list_t *)vector_at(&ht->tables, index);
    list_delete(lt, node);
    list_node_destroy(node);
    pthread_mutex_unlock(&ht->lock);
    return 0;
  }
  return -1;
}
void *hashtable_search(hashtable_t *ht, void *key,uint64_t hash)
{
  list_node_t *node = (list_node_t *)hashtable_search_node(ht, key,hash);
  void *result = NULL;
  if (node != NULL)
  {
    result = node->value;
  }
  return result;
}
void hashtable_deinit(hashtable_t *ht)
{
  if (ht != NULL)
  {
    for (uint32_t i = 0; i < ht->max_bucket; i++)
    {
      list_t *lt = (list_t *)vector_at(&ht->tables, i);
      if (lt != NULL && lt->size > 0)
      {
        list_destroy(lt);
      }
    }
    vector_deinit(&ht->tables);
  }
}
void hashtable_destroy(hashtable_t *ht)
{
  if(ht!=NULL) {
    hashtable_deinit(ht);
    free(ht);
  }
}
size_t hashtable_size(hashtable_t *ht){
   return ((ht==NULL)?0:(vector_size(&ht->tables)));
}