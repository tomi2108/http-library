#include "response.h"

void response_send(Response *res, int socket) {
  char *word = status[res->status_code];
  char status_code[4] = {0};
  snprintf(status_code, 4, "%d", res->status_code);

  t_buffer *buf = buffer_create();
  buffer_add_string(buf, 9, "HTTP/1.1 ");
  buffer_add_string(buf, strlen(status_code), status_code);
  buffer_add_string(buf, 1, " ");
  buffer_add_string(buf, strlen(word), word);
  buffer_add_string(buf, 4, "\r\n\r\n");

  write(socket, buf->stream, buf->size);

  buffer_destroy(buf);
  response_destroy(res);
}

Response *response_create() {
  Response *response = malloc(sizeof(Response));
  if (response == NULL)
    return NULL;
  return response;
}

void response_destroy(Response *res) { free(res); }
