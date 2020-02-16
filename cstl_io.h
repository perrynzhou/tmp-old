/*************************************************************************
  > File Name: cstl_io.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Fri 14 Feb 2020 06:43:29 PM CST
 ************************************************************************/

#ifndef _CSTL_IO_H
#define _CSTL_IO_H
#include <unistd.h>
ssize_t write_n(int fd, const void *buf, size_t len);
ssize_t read_n(int fd, void *buf, size_t len);
#endif
