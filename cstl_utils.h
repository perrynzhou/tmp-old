/*************************************************************************
  > File Name: cstl_utils.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 16 Feb 2020 02:28:25 PM CST
 ************************************************************************/

#ifndef _CSTL_UTILS_H
#define _CSTL_UTILS_H
#include <stdint.h>
#include <stdio.h>
void fetch_sock_addr_info(int fd, char *str,size_t str_len);
uint64_t fetch_timestamp();
#endif
