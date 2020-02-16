/*************************************************************************
  > File Name: cstl_hashtable.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sat 15 Feb 2020 08:33:07 PM CST
 ************************************************************************/

#ifndef _CSTL_HASHTABLE_H
#define _CSTL_HASHTABLE_H
#include "cstl_def.h"
hashtable_t *hashtable_create(uint32_t max_buckets,cstl_cmp_fn fn);
int hashtable_init(hashtable_t *ht, uint32_t max_buckets,cstl_cmp_fn fn);
//return data insert timestamp,that as unique id for data
int hashtable_insert(hashtable_t *ht, void *data,uint64_t hash);
int hashtable_delete(hashtable_t *ht, void *key,uint64_t hash);
void *hashtable_search(hashtable_t *ht, void *key,uint64_t hash);
void hashtable_deinit(hashtable_t *ht);
void hashtable_destroy(hashtable_t *ht);
size_t hashtable_size(hashtable_t *ht);
uint32_t hashtable_limit_size(hashtable_t *ht);
#endif
