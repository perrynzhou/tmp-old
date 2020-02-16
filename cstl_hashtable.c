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
static inline  uint64_t hashtable_fetch_timestamp()
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
static inline  hashtable_entry_t  *hashtable_entry_create(void *data) {
     hashtable_entry_t *het = (hashtable_entry_t *)calloc(1,sizeof(hashtable_entry_t));
     if(het!=NULL) {
       het->data = data;
       het->timestamp = hashtable_fetch_timestamp();
     }
     return het;
}
static void hashtable_entry_destroy(hashtable_entry_t *het) {
   if(het !=NULL) {
      free(het);
      het=NULL;
   }
}
int hashtable_init(hashtable_t *ht, uint32_t max_buckets, uint32_t link_limit)
{
  if (ht != NULL)
  {
    vector_init(&ht->tables, max_buckets);
    ht->link_limit = link_limit;
    return 0;
  }
  return -1;
}
hashtable_t *hashtable_create(uint32_t max_buckets, uint32_t link_limit)
{
  hashtable_t *ht = (hashtable_t *)calloc(1, sizeof(hashtable_t));
  if (ht != NULL)
  {
    if (hashtable_init(ht, link_limit, max_buckets) != 0)
    {
      free(ht);
      ht = NULL;
    }
  }
  return ht;
}

//return data insert timestamp,that as unique id for data
uint64_t hashtable_insert(hashtable_t *ht, uint64_t hash, void *data)
{
  uint64_t index = hashtable_jump_consistent(hash,ht->max_bucket);
  list_t *lt = vector_at(&ht->tables,index);
  if(lt==NULL) {
     lt = list_create(NULL);
     vector_push_back(&ht->tables,lt);
  }
  if(ht->link_limit>0 && lt->size>ht->link_limit){
    return 0;
  }
  hashtable_entry_t *het = hashtable_entry_create(data);
  assert(het!=NULL);
  list_node_t *node = list_node_create(het);
  assert(node!=NULL);
  list_insert(lt,node);
  return  het->timestamp;

}
int hashtable_delete(hashtable_t *ht, uint64_t hash, int64_t data_timestamp)
{
  if(ht!=NULL) {
      uint64_t index = hashtable_jump_consistent(hash,ht->max_bucket);
      list_t *lt = vector_at(&ht->tables,index);
      if(lt!=NULL) {
        list_node_t *cur = lt->head;
        while(cur!=NULL) {
           list_node_t *next = cur->next;
           hashtable_entry_t *het = (hashtable_entry_t *)cur->value;
        }
      }
  }
}
void *hashtable_search(hashtable_t *ht, uint64_t hash, int64_t data_timestamp)
{
}
void hashtable_deinit(hashtable_t *ht)
{
}
void hashtable_destroy(hashtable_t *ht)
{
}