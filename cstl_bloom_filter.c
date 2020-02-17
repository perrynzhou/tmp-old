/*************************************************************************
  > File Name: cstl_bloom_filter.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 16 Feb 2020 02:10:28 PM CST
 ************************************************************************/

#include "cstl_bloom_filter.h"
#include "cstl_vector.h"
#include "cstl_def.h"
#include <stdlib.h>
#include <stdlib.h>
#define CSTL_BLOOM_FILTER_SHIFT (3)
#define CSTL_BLOOM_FILTER_MASK (0x7)
#define CSTL_BLOOM_FILTER_DEFAULT_HASH_RANGE (16384)
#define CSTL_BLOOM_FILTER_BASE_BIT (8)
bloom_filter_t *bloom_filter_create(uint64_t max_hash_range)
{
  bloom_filter_t *bf = (bloom_filter_t *)calloc(1, sizeof(bloom_filter_t));
  if (bf != NULL)
  {
    if (bloom_filter_init(bf, max_hash_range) != 0)
    {
      free(bf);
    }
  }
  return bf;
}
int bloom_filter_init(bloom_filter_t *bf, uint64_t max_hash_range)
{
  if (bf != NULL)
  {
    uint64_t real_max_hash = (max_hash_range < CSTL_BLOOM_FILTER_DEFAULT_HASH_RANGE) ? CSTL_BLOOM_FILTER_DEFAULT_HASH_RANGE : max_hash_range;
    real_max_hash = (real_max_hash / CSTL_BLOOM_FILTER_BASE_BIT) + 1;
    bf->bitmap = (uint8_t *)calloc(real_max_hash >> 3, sizeof(uint8_t));
    if (bf->bitmap != NULL)
    {
      vector_init(&bf->fn, 0);
      return 0;
    }
  }
  return -1;
}
void bloom_filter_pushback_hashfn(bloom_filter_t *bf, cstl_hash_fn fn)
{
  if (bf != NULL && fn != NULL)
  {
    vector_push_back(&bf->fn, fn);
  }
}
void bloom_filter_put(bloom_filter_t *bf, const void *key, size_t len)
{
  if (bf != NULL && key != NULL)
  {
    for (uint32_t i = 0; i < vector_size(&bf->fn); i++)
    {
      cstl_hash_fn fn = (cstl_hash_fn)vector_at(&bf->fn, i);
      uint64_t n = fn(key, len);
      bf->bitmap[n >> CSTL_BLOOM_FILTER_SHIFT] |= (1 << (n & CSTL_BLOOM_FILTER_MASK));
    }
  }
}
uint8_t bloom_filter_get(bloom_filter_t *bf, const void *key, size_t len)
{
  uint8_t test = 1;
  if (bf != NULL && key != NULL)
  {
    for (uint32_t i = 0; i < vector_size(&bf->fn); i++)
    {
      cstl_hash_fn fn = (cstl_hash_fn)vector_at(&bf->fn, i);
      uint64_t n = fn(key, len);
      if (!(bf->bitmap[n >> CSTL_BLOOM_FILTER_SHIFT] | (1 << (n & CSTL_BLOOM_FILTER_MASK))))
      {
        test = 0;
        break;
      }
    }
  }
  return test;
}
void bloom_filter_destroy(bloom_filter_t *bf)
{
  if (bf != NULL)
  {
    bloom_filter_deinit(bf);
    free(bf);
    bf = NULL;
  }
}
void bloom_filter_deinit(bloom_filter_t *bf)
{
  if (bf != NULL)
  {
    vector_deinit(&bf->fn);
    free(bf->bitmap);
  }
}