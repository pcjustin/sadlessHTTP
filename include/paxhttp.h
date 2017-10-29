#ifndef __PAXHTTP_H__
#define __PAXHTTP_H__

#include <stddef.h>
#define HTTP_VERSION "paxhttp2 0.1"
#define HTTP_SOCKET_SIZE 3 
typedef struct PAXHTTP_SOCKET {
  int (*net_open)(char *address, int port);
  int (*net_close)(int s);
  int (*net_send)(int s, void *buffer, size_t size);
  int (*net_recv)(int s, void *buffer, size_t size);
} PAXHTTP_SOCKET;

int paxHttpGetVersion(char *version, size_t size);
int paxHttpCreate(void);
int paxHttpConnect(int session, char *url);
int paxHttpClose(int session);
int paxHttpSetSocket(int session, PAXHTTP_SOCKET *net_socket);
#endif
