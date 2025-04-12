#ifndef SERVER_H_
#define SERVER_H_

#include "buffer.h"
#include "list.h"
#include "request.h"
#include "response.h"
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void (*Handler)(Request *req, Response *res);

typedef struct Endpoint {
  char *pathname;
  Method method;
  Handler callback;
} Endpoint;

typedef struct HttpServer {
  Endpoint *endpoints;
} HttpServer;

HttpServer *server_init();
int server_listen(HttpServer *server, char *port, void (*callback)());
void server_endpoint(HttpServer *server, Method method, const char *path,
                     Handler handler);

#endif
