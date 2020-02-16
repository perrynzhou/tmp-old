/*************************************************************************
  > File Name: cstl_bloom_filter.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 16 Feb 2020 02:10:28 PM CST
 ************************************************************************/


#include "cstl_bloom_filter.h"
#include "cstl_def.h"
#include "cstl_vector.h"
#include <stdlib.h>
#define CSTL_BLOOM_FILTER_DEFAULT_HASH_RANGE  16384
#define CSTL_BASE_BIT   (8)
bloom_filter_t *bloom_filter_create(uint64_t max_hash_range){
  bloom_filter_t *bf = (bloom_filter_t *)calloc(1,sizeof(bloom_filter_t));
  if(bf!=NULL) {
    if(bloom_filter_init(bf,max_hash_range)!=0) {
      free(bf);
    }
  }
  return bf;
} 
int bloom_filter_init(bloom_filter_t *bf,uint64_t max_hash_range){
  if(bf !=NULL) {
   uint64_t real_max_hash = (max_hash_range<CSTL_BLOOM_FILTER_DEFAULT_HASH_RANGE)?CSTL_BLOOM_FILTER_DEFAULT_HASH_RANGE:max_hash_range;
   real_max_hash = real_max_hash&(CSTL_BASE_BIT-1);
   bf->data = (uint8_t *)calloc(real_max_hash>>3,sizeof(uint8_t));
   if(bf->data!=NULL) {
      vector_init(&bf->fn,0);
      return 0;
   }
  }
  return -1;
}
void bloom_filter_pushback_hashfn(bloom_filter_t *bf,cstl_hash_fn fn){
    if(bf!=NULL && fn!=NULL) {
       vector_push_back(&bf->fn,fn);
    }
}
uint8_t bloom_filter_put(const void *key,size_t len){
  
}
uint8_t bloom_filter_get(const void  *key,size_t len){
  
}
void bloom_filter_destroy(bloom_filter_t *bf){
   if(bf!=NULL) {
     bloom_filter_deinit(bf);
     free(bf);
      bf = NULL;
   }
}
void bloom_filter_deinit(bloom_filter_t *bf){
  if(bf!=NULL) {
      vector_deinit(&bf->fn);
      free(bf->data);
     
  }
}