/*************************************************************************
  > File Name: cstl_netsocket_t.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Sun 09 Feb 2020 10:33:47 AM CST
 ************************************************************************/

#ifndef _CSTL_netsocket_t_H
#define _CSTL_netsocket_t_H
#include "cstl_def.h"
#include <ev.h>
int netsocket_init(netsocket_t *ns, const char *addr, int port, int backlog);
void netsocket_start(netsocket_t *ns);
void netsocket_deinit(netsocket_t *ns);
#endif
