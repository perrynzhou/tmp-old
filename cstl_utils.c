/*************************************************************************
  > File Name: cstl_utils.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 16 Feb 2020 02:28:29 PM CST
 ************************************************************************/

#include "cstl_utils.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
void fetch_sock_addr_info(int fd, char *str,size_t str_len)
{
  struct sockaddr ip_addr_struct;
  socklen_t len = sizeof(ip_addr_struct);
  getpeername(fd, (struct sockaddr *)&ip_addr_struct, &len);
  struct sockaddr_in *s = (struct sockaddr_in *)&ip_addr_struct;
  int port = ntohs(s->sin_port);
  char ip_addr[64] = {'\0'};
  inet_ntop(AF_INET, &s->sin_addr, (char *)&ip_addr, 64);
  snprintf(str,str_len, "%s:%d", ip_addr, port);
}
uint64_t fetch_timestamp() {
   struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)(tv.tv_sec * 1000000 + tv.tv_usec);
}