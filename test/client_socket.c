#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <paxhttp_err.h>
#include "client_socket.h"
int net_open(char *address, int port) {
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Fail to create a socket.\r\n");
    return PAXHTTP_FAILURE;
  }
  struct sockaddr_in info;
  bzero(&info,sizeof(info));
  info.sin_family = AF_INET;
//   info.sin_addr.s_addr = inet_addr(address);
  info.sin_port = htons(port);
  inet_pton(AF_INET, address, &info.sin_addr);
  int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
  if(err==-1) {
    printf("Connection error\r\n");
    return PAXHTTP_FAILURE;
  }
  return sockfd;
}
int net_close(int s) {
  if (s < 0) {
    return PAXHTTP_FAILURE;
  }
  close(s);
  return PAXHTTP_SUCCESS;
}
int net_send(int s, void *buffer, size_t size) {
  int ret;
  ret = send(s, buffer, size, 0);
  return ret;
}
int net_recv(int s, void *buffer, size_t size) {
  int ret;
  ret = recv(s, buffer, size, 0);
  return ret;
}