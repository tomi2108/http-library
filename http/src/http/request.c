#include "request.h"
#include "buffer.h"
#include <stdint.h>
#include <string.h>
#include <unistd.h>

void request_parse(Request *req) {
  char *stream = req->buffer->stream;

  char *line = strtok(stream, "\r\n");
  char version[16];
  sscanf(line, "%7s %1023s %15s", req->method, req->path, version);
}

void request_send(Request *req, char *path) {}

Request *request_create() {
  Request *request = malloc(sizeof(Request));
  if (request == NULL)
    return NULL;

  request->buffer = buffer_create();
  return request;
}

Request *request_recieve(int socket) {
  Request *request = request_create();

  char stream[1024] = {0};
  int recieved = read(socket, stream, 1000);
  stream[recieved] = 0;
  buffer_add_string(request->buffer, recieved, stream);

  request_parse(request);
  return request;
}
