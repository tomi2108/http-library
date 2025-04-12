#include "../include/request.h"
#include <stdlib.h>

void request_parse(Request *req) {
  // parse buffer and initialize request
  req->method = GET;
}

Request *request_create() {
  Request *request = malloc(sizeof(Request));
  if (request == NULL)
    return NULL;

  request->buffer = buffer_create();
  return request;
}

Request *request_recieve(int socket) {
  Request *request = request_create();
  int req_size = 1;

  request->buffer->stream = malloc(req_size);
  if (request->buffer->stream == NULL)
    return NULL;

  int err_stream = recv(socket, request->buffer->stream, req_size, MSG_WAITALL);
  if (err_stream == 0)
    return NULL;

  request_parse(request);
  return request;
}
