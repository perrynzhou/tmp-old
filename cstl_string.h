/*************************************************************************
  > File Name: cstl_string.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Mon 28 Oct 2019 02:22:06 PM CST
 ************************************************************************/

#ifndef _CSTL_STRING_H
#define _CSTL_STRING_H
#include "cstl_def.h"
int string_format_init(string_t *se, const char *fmt, ...);
int string_init(string_t *se, const char *value);
string_t *string_create(const char *value);
string_t *string_format_create(const char *fmt, ...);
int string_copy_substring(string_t *se, const char *str, size_t n);
int string_replace(string_t *se, const char *value);
int string_reverse(string_t *se);
int string_append(string_t *se,const char *src);
int string_copy(string_t *dest, string_t *src);
void string_print(string_t *se);
void string_deinit(string_t *se);
void string_destroy(string_t *se);
const char *string_value(string_t *se);
size_t string_length(string_t *se);
const char *string_at(string_t *se, size_t index);
#endif
