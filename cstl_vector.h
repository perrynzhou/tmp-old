/*************************************************************************
  > File Name: cstl_vector_t.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Tue 31 Dec 2019 05:43:53 PM CST
 ************************************************************************/

#ifndef _CSTL_VECTOR_H
#define _CSTL_VECTOR_H
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include "cstl_def.h"
vector_t *vector_create(uint64_t cap);
int vector_init(vector_t *vec,uint64_t cap);
int vector_push_back(vector_t *vec, void *data);
int vector_reserve(vector_t *vec);
int vector_insert(vector_t *vec, uint64_t index, void *data);
void vector_deinit(vector_t *vec);
void vector_destroy(vector_t *vec);
void *vector_at(vector_t *vec, uint64_t index);
void vector_print(vector_t *vec);
size_t vector_size(vector_t *vec);
size_t vector_cap(vector_t *vec);
#endif
