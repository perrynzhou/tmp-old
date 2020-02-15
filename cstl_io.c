/*************************************************************************
  > File Name: cstl_io.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Fri 14 Feb 2020 06:43:33 PM CST
 ************************************************************************/

#include "cstl_io.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
ssize_t write_n(int fd, const void *buf, size_t len)
{
  int writen = 0;
  while (writen < len)
  {
    ssize_t w = write(fd, (const char *)buf + writen, len - writen);
    if (w > 0)
    {
      writen += w;
    }
    else if (w == 0)
    {
      break;
    }
    else if (errno != EINTR)
    {
      fprintf(stdout, "write error: %s(errno: %d)\n", strerror(errno), errno);
      break;
    }
  }
  return writen;
}
ssize_t read_n(int fd, void *buf, size_t len)
{
  int readn = 0;
  while (readn < len)
  {
    ssize_t r = read(fd, (char *)buf + readn, len - readn);
    if (r > 0)
    {
      readn += r;
    }
    else if (r == 0)
    {
      break;
    }
    else if (r != EINTR)
    {
      printf("read error: %s(errno: %d)\n", strerror(errno), errno);
      break;
    }
  }
  return readn;
}