#include "response.h"
#include "list.h"
#include "protocol.h"

void response_send(Response *res, int socket) {
  char *word = status[res->status_code];
  char status_code[4] = {0};
  snprintf(status_code, 4, "%d", res->status_code);

  t_buffer *buf = buffer_create();
  buffer_add_string(buf, 9, "HTTP/1.1 ");
  buffer_add_string(buf, strlen(status_code), status_code);
  buffer_add_string(buf, 1, " ");
  buffer_add_string(buf, strlen(word), word);
  buffer_add_string(buf, 2, "\r\n");

  t_list_iterator *headers_iterator = list_iterator_create(res->headers);
  while (list_iterator_has_next(headers_iterator)) {
    Header *header = list_iterator_next(headers_iterator);
    buffer_add_string(buf, strlen(header->key), header->key);
    buffer_add_string(buf, 2, ": ");
    buffer_add_string(buf, strlen(header->value), header->value);
    buffer_add_string(buf, 2, "\r\n");
  }
  list_iterator_destroy(headers_iterator);

  if (res->body->size > 0) {
    buffer_add_string(buf, 2, "\r\n");
    buffer_add_string(buf, res->body->size, res->body->stream);
    buffer_add_string(buf, 2, "\r\n");
  }

  write(socket, buf->stream, buf->size);

  buffer_destroy(buf);
  response_destroy(res);
}

Response *response_create() {
  Response *response = malloc(sizeof(Response));
  if (response == NULL)
    return NULL;
  response->headers = headers_create();
  response->body = body_create();
  return response;
}

void response_destroy(Response *res) {
  if (res->body != NULL)
    body_destroy(res->body);
  if (res->headers != NULL)
    headers_destroy(res->headers);
  free(res);
}
