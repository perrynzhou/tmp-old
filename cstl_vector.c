/*************************************************************************
  > File Name: cstl_vector_t.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Tue 31 Dec 2019 05:44:02 PM CST
 ************************************************************************/

#include "cstl_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <pthread.h>
#define CSTL_VECTOR_INIT_SIZE (4)
#define CSTL_VECTOR_GROW_RATE (0.75)
vector_t *vector_create()
{
  vector_t *vec = (vector_t *)calloc(1, sizeof(vector_t));
  assert(vec != NULL);
  if (vector_init(vec) != 0)
  {
    free(vec->tables);
    return NULL;
  }
  return vec;
}
int vector_init(vector_t *vec)
{
  if (vec != NULL)
  {
    vec->cap = CSTL_VECTOR_INIT_SIZE;
    vec->size = 0;
    pthread_mutex_init(&vec->lock, NULL);
    vec->tables = (void **)calloc(vec->cap, sizeof(void *));
    assert(vec->tables);
    return 0;
  }
  return -1;
}
static int vector_expand(vector_t *vec)
{
  void **tables = (void **)calloc(vec->cap * 2, sizeof(void *));
  if (tables != NULL)
  {
    for (uint64_t i = 0; i < vec->size; i++)
    {
      tables[i] = vec->tables[i];
    }
    free(vec->tables);
    vec->tables = tables;
    vec->cap = vec->cap * 2;
    return 0;
  }
  return -1;
}
int vector_reserve(vector_t *vec)
{
  if (vec != NULL)
  {
    pthread_mutex_lock(&vec->lock);
    free(vec->tables[vec->size]);
    vec->cap=(vec->size%CSTL_VECTOR_INIT_SIZE==0)?(vec->size):((vec->size/CSTL_VECTOR_INIT_SIZE)+1)*CSTL_VECTOR_INIT_SIZE;
    pthread_mutex_unlock(&vec->lock);
  }
}
void vector_print(vector_t *vec)
{
  if (vec != NULL)
  {
    fprintf(stdout, "vector size:%d\n", vec->size);
    fprintf(stdout, "vector cap:%d\n", vec->cap);
  }
}
int vector_insert(vector_t *vec, uint64_t index, void *data)
{
  int ret = -1;
  if (data != NULL)
  {
    pthread_mutex_lock(&vec->lock);
    if (vec->size == vec->cap)
    {
      if (vector_expand(vec) != 0)
      {
        pthread_mutex_unlock(&vec->lock);
        return ret;
      }
    }
    vec->tables[index] = data;
    pthread_mutex_unlock(&vec->lock);
    ret = 0;
  }
  return ret;
}
int vector_push_back(vector_t *vec, void *data)
{
  if (data != NULL)
  {
    pthread_mutex_lock(&vec->lock);
    double rate = (double)(vec->size / vec->cap);
    if (rate >= CSTL_VECTOR_GROW_RATE)
    {
      if (vector_expand(vec) != 0)
      {
        pthread_mutex_unlock(&vec->lock);
        return -1;
      }
    }
    vec->tables[vec->size++] = data;
    pthread_mutex_unlock(&vec->lock);
    return 0;
  }
  return -1;
}
inline void *vector_at(vector_t *vec, uint64_t index)
{
  if (index < vec->size)
  {
    return vec->tables[index];
  }
  return NULL;
}
void vector_deinit(vector_t *vec)
{
  if (vec != NULL)
  {
    pthread_mutex_lock(&vec->lock);
    free(vec->tables);
    vec->tables = NULL;
    vec->size = 0;
    vec->cap = 0;
    pthread_mutex_unlock(&vec->lock);
  }
}
inline size_t vector_size(vector_t *vec){
      return vec->size;
    
    
}
size_t vector_cap(vector_t *vec){
   return vec->cap;
}
void vector_destroy(vector_t *vec)
{
  if (vec != NULL)
  {
    vector_deinit(vec);
    free(vec);
    vec = NULL;
  }
}

#ifdef CSTL_VECTOR_TEST
#include <stdlib.h>
int main(int argc, char *argv[])
{
  vector_t *vec = vector_create();
  size_t sz = 1024 * 32;
  for (uint64_t i = 0; i < sz; i++)
  {
    int *c = calloc(1, sizeof(int));
    *c = rand() % 1024;
    if(vector_size(vec)==133) {
      vector_reserve(vec);
      vector_print(vec);
    }
    vector_push_back(vec, c);
  }
  vector_destroy(vec);
  return 0;
}
#endif