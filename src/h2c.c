#include <stdio.h>
#include <stdlib.h>

#include <paxhttp.h>
#include <paxhttp_err.h>
#include <paxhttp_internal.h>

// extern PAXHTTP_SOCKET net_sockets[HTTP_SOCKET_SIZE];
int writeH2C_Header(int session, int sockfd, char *payload, size_t size) {
  PAXHTTP_SOCKET *net_socket;
  if (session < 0 || session > HTTP_SOCKET_SIZE) {
    return PAXHTTP_FAILURE;
  } else {
    net_socket = &net_sockets[session];
  }
  char *header;
  int ret;
  ret = snprintf(NULL, 0, "GET / HTTP/1.1\r\n" \
                 "Host: nghttp2.org\r\n" \
                 "User-Agent: curl/7.54.0\r\n" \
                 "Accept: */*\r\n" \
                 "Connection: Upgrade, HTTP2-Settings\r\n" \
                 "Upgrade: h2c\r\n" \
                 "HTTP2-Settings: AAMAAABkAARAAAAAAAIAAAAA\r\n\r\n");
  header = (char *)malloc(ret);
  ret = snprintf(header, ret+1, "GET / HTTP/1.1\r\n" \
                 "Host: nghttp2.org\r\n" \
                 "User-Agent: curl/7.54.0\r\n" \
                 "Accept: */*\r\n" \
                 "Connection: Upgrade, HTTP2-Settings\r\n" \
                 "Upgrade: h2c\r\n" \
                 "HTTP2-Settings: AAMAAABkAARAAAAAAAIAAAAA\r\n\r\n");
  ret = net_socket->net_send(sockfd, header, ret);
  free(header);
  return PAXHTTP_SUCCESS;
}