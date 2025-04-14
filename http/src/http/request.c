#include "request.h"
#include <string.h>

void request_parse(Request *req) {
  const char *body_separator = "\r\n\r\n";

  char *stream = malloc(req->buffer->size);
  strcpy(stream, req->buffer->stream);

  char *body_start = strstr(stream, body_separator);
  body_start[0] = '\0';
  char *body = body_start + 4;
  body[strlen(body) - 1] = '\0';
  body_add_string(req->body, body, strlen(body));

  char *end_str;
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
  free(stream);
}

void request_send(Request *req, Path path) {}

Request *request_create() {
  Request *request = malloc(sizeof(Request));
  if (request == NULL)
    return NULL;

  request->buffer = buffer_create();
  request->headers = headers_create();
  request->body = body_create();
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
