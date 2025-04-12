#ifndef SERVER_H_
#define SERVER_H_

#include "buffer.h"
#include "list.h"
#include "request.h"
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Endpoint {
  char *pathname;
  Method method;
  void (*callback)();
} Endpoint;

typedef struct HttpServer {
  Endpoint *endpoints;
} HttpServer;

HttpServer *server_init();
int server_listen(HttpServer *server, char *port,void (*callback)());

#endif
