#include <stdio.h>
#include <stdlib.h>
#include <paxhttp.h>
#include <paxhttp_err.h>
#include "client_socket.h"

#define REMOTE_ADDRESS "127.0.0.1"
#define REMOTE_PORT 8080

int main(int argc, char *argv[]) {
  int ret, s1, s2, s3;
  char *version, *pUrl;
  PAXHTTP_SOCKET tcp_socket = {
    net_open,
    net_close,
    net_send,
    net_recv,
  };
  //
  ret = paxHttpGetVersion(NULL, 0);
  version = (char*)malloc(ret);
  ret = paxHttpGetVersion(version, ret);
  printf("version: %s\r\n", version);
  free(version);
  //
  ret = snprintf(NULL, 0, "http://%s:%d", REMOTE_ADDRESS, REMOTE_PORT);
  ret += 1; // add '\0'
  pUrl = (char*)malloc(ret);
  ret = snprintf(pUrl, ret, "http://%s:%d", REMOTE_ADDRESS, REMOTE_PORT);
  printf("pUrl: %s\r\n", pUrl);
  s1 = paxHttpCreate();
  ret = paxHttpSetSocket(s1, &tcp_socket);
  ret = paxHttpConnect(s1, pUrl);
  free(pUrl);
  ret = paxHttpClose(s1);
  return PAXHTTP_SUCCESS;
}