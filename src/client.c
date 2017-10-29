#include <stdio.h>
#include <string.h>
#include <paxhttp.h>
#include <paxhttp_err.h>
#include <paxhttp_internal.h>
#include <spinlock.h>

int paxHttpGetVersion(char *version, size_t size) {
  if (version) {
    memcpy(version, HTTP_VERSION, size);
  }
  return sizeof(HTTP_VERSION);
}
static int sessions[HTTP_SOCKET_SIZE];
static int session;
// PAXHTTP_SOCKET net_sockets[HTTP_SOCKET_SIZE];
int paxHttpCreate(void) {
  int i=0;
  size_t size;
  size = sizeof(session);
  for (i=0; i<size; i++) {
    if (sessions[i] == 0) {
      memset(sessions, 0x0, sizeof(int)*HTTP_SOCKET_SIZE);
      memset(net_sockets, 0x0, sizeof(PAXHTTP_SOCKET)*HTTP_SOCKET_SIZE);
      spin_lock();
      session = i;
      sessions[i] = 1;
      spin_unlock();
      break;
    }
  }
  return session;
}

int paxHttpConnect(int session, char *url) {
  PAXHTTP_SOCKET *net_socket;
  int s, ret;
  if (session < 0 || session > HTTP_SOCKET_SIZE) {
    return PAXHTTP_FAILURE;
  } else {
    net_socket = &net_sockets[session];
  }
  // parse URL to address and port and something else
  s = net_socket->net_open("139.162.123.134", 80);
  char recv[16384];
  ret = writeH2C_Header(session, s, recv, ret);
  ret =net_socket->net_recv(s, recv, sizeof(recv));
  printf("recv: %s", recv);
  return PAXHTTP_SUCCESS;
}

int paxHttpClose(int session) {
  PAXHTTP_SOCKET *net_socket;
  if (session < 0 || session > HTTP_SOCKET_SIZE) {
    return PAXHTTP_FAILURE;
  } else {
    net_socket = &net_sockets[session];
  }
  spin_lock();
  sessions[session] = 0;
  spin_unlock();
  net_socket->net_close(session);
  printf("session %d is destroy\r\n", session);
  return PAXHTTP_SUCCESS;
}

int paxHttpSetSocket(int session, PAXHTTP_SOCKET *net_socket) {
  if (session < 0 || session > HTTP_SOCKET_SIZE) {
    return PAXHTTP_FAILURE;
  }
  spin_lock();
  memcpy(&net_sockets[session], net_socket, sizeof(PAXHTTP_SOCKET));
  spin_unlock();
  return PAXHTTP_SUCCESS;
}