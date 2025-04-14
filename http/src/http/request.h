#ifndef REQUEST_H_
#define REQUEST_H_

#include "buffer.h"
#include "list.h"
#include "protocol.h"
#include <netdb.h>
#include <unistd.h>

typedef struct Request {
  t_buffer *buffer;
  Method method;
  Path path;
  Body body;
  Headers headers;
} Request;

Request *request_create();
Request *request_recieve(int socket);
void request_send(Request *req, Path path);

#endif
