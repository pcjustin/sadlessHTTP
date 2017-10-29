#ifndef __CLIENT_SOCKET_H__
#define __CLIENT_SOCKET_H__

#include <stddef.h>
int net_open(char *address, int port);
int net_close(int s);
int net_send(int s, void *buffer, size_t size);
int net_recv(int s, void *buffer, size_t size);
#endif
