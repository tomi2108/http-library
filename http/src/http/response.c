#include "response.h"

void response_send(Response *res, int socket) {}

Response *response_create() {
  Response *response = malloc(sizeof(Response));
  if (response == NULL)
    return NULL;

  response->buffer = buffer_create();
  return response;
}
