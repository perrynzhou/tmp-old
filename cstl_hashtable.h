/*************************************************************************
  > File Name: cstl_hashtable.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sat 15 Feb 2020 08:33:07 PM CST
 ************************************************************************/

#ifndef _CSTL_HASHTABLE_H
#define _CSTL_HASHTABLE_H
#include "cstl_def.h"
hashtable_t *hashtable_create(uint64_t cap,uint32_t link_limit);
int hashtable_init(hashtable_t *ht, uint32_t link_limit);
//return data insert timestamp,that as unique id for data
int64_t hashtable_insert(hashtable_t *ht, uint64_t hash, void *data);
int hashtable_delete(hashtable_t *ht, uint64_t hash, int64_t data_timestamp);
void *hashtable_search(hashtable_t *ht, uint64_t hash, int64_t data_timestamp);
void hashtable_deinit(hashtable_t *ht);
void hashtable_destroy(hashtable_t *ht);
#endif
