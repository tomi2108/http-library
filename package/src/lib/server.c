#include "../include/server.h"

HttpServer *server_init() {
  HttpServer *server = malloc(sizeof(HttpServer));
  return server;
}

void server_endpoint(HttpServer *server, Method method, const char *path,
                     void (*callback)()) {
  callback();
}

int server_listen(HttpServer *server, char *port, void (*callback)()) {
  // consider moving to server_init && HttpServer struct
  struct addrinfo hints;
  struct addrinfo *server_info;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int err_get_addr = getaddrinfo(NULL, port, &hints, &server_info);
  if (err_get_addr != 0)
    return -1;

  int fd_socket = socket(server_info->ai_family, server_info->ai_socktype,
                         server_info->ai_protocol);
  if (fd_socket == -1)
    return -1;

  int err_bind = bind(fd_socket, server_info->ai_addr, server_info->ai_addrlen);
  if (err_bind == -1)
    return -1;

  int err_listen = listen(fd_socket, SOMAXCONN);
  if (err_listen == -1)
    return -1;

  freeaddrinfo(server_info);

  callback();
  while (1) {
    int client_socket = accept(fd_socket, NULL, NULL);
    if (client_socket == -1)
      continue;
    Request *req = request_recieve(client_socket);

    // TODO: exec corresponding callback
    close(client_socket);
  }
  close(fd_socket);
}
