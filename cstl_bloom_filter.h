/*************************************************************************
  > File Name: cstl_bloom_filter.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 16 Feb 2020 02:10:24 PM CST
 ************************************************************************/

#ifndef _CSTL_BLOOM_FILTER_H
#define _CSTL_BLOOM_FILTER_H
#include "cstl_def.h"
bloom_filter_t *bloom_filter_create(uint64_t max_hash_range);
int bloom_filter_init(bloom_filter_t *bf,uint64_t max_hash_range);
void bloom_filter_pushback_hashfn(bloom_filter_t *bf,cstl_hash_fn fn);
uint8_t bloom_filter_put(const void *key,size_t len);
uint8_t bloom_filter_get(const void  *key,size_t len);
void bloom_filter_destroy(bloom_filter_t *bf);
void bloom_filter_deinit(bloom_filter_t *bf);
#endif
