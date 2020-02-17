/*************************************************************************
  > File Name: cstl_bloom_filter.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 16 Feb 2020 02:10:24 PM CST
 ************************************************************************/

#ifndef _CSTL_BLOOM_FILTER_H
#define _CSTL_BLOOM_FILTER_H
#include "cstl_def.h"
#include <stdbool.h>
bloom_filter_t *bloom_filter_create(uint64_t max_hash_range);
int bloom_filter_init(bloom_filter_t *bf,uint64_t max_hash_range);
void bloom_filter_pushback_hashfn(bloom_filter_t *bf,cstl_hash_fn fn);
void  bloom_filter_put(bloom_filter_t *bf,const void *key,size_t len);
bool bloom_filter_get(bloom_filter_t *bf,const void  *key,size_t len);
void bloom_filter_destroy(bloom_filter_t *bf);
void bloom_filter_deinit(bloom_filter_t *bf);
#endif
