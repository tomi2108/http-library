#include "request.h"
#include "buffer.h"
#include "protocol.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void request_parse(Request *req) {
  char *stream = malloc(req->buffer->size);
  char *end_str;
  strcpy(stream, req->buffer->stream);

  char *line = strtok_r(stream, "\r\n", &end_str);
  // TODO: Do something with version probably... ?
  char version[16] = {0};
  sscanf(line, "%7s %1023s %15s", req->method, req->path, version);

  line = strtok_r(NULL, "\r\n", &end_str);
  while (line != NULL) {
    char *end_token;
    char *header = malloc(strlen(line) + 1);
    strcpy(header, line);
    char *key = strtok_r(header, ":", &end_token);
    char *value = strtok_r(NULL, "", &end_token);
    if (value[0] == ' ')
      value = &value[1];

    headers_add(req->headers, key, value);
    line = strtok_r(NULL, "\r\n", &end_str);
    free(header);
  }
}

void request_send(Request *req, Path path) {}

Request *request_create() {
  Request *request = malloc(sizeof(Request));
  if (request == NULL)
    return NULL;

  request->buffer = buffer_create();
  request->headers = headers_create();
  return request;
}

Request *request_recieve(int socket) {
  Request *request = request_create();

  // TODO: Using fixed sizes seems off... read RFC: 2616
  // may need to implement a proper parser =)
  char stream[1024] = {0};
  int recieved = read(socket, stream, 1000);
  stream[recieved] = 0;
  buffer_add_string(request->buffer, recieved, stream);

  request_parse(request);
  return request;
}
