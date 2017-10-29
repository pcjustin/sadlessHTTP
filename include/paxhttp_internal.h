#ifndef __PAXHTTP_INTERNAL_H__
#define __PAXHTTP_INTERNAL_H__

#include <paxhttp.h>
PAXHTTP_SOCKET net_sockets[HTTP_SOCKET_SIZE];
int writeH2C_Header(int session, int sockfd, char *payload, size_t size);
#endif
