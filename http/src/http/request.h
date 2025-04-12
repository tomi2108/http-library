#ifndef REQUEST_H_
#define REQUEST_H_

#include "buffer.h"
#include "protocol.h"
#include <netdb.h>

typedef struct Request {
  t_buffer *buffer;
  Method method;
} Request;

Request *request_create();
Request *request_recieve(int socket);
void request_send(Request *req, char *path);

#endif
