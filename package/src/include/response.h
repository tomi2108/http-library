#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "buffer.h"
#include "protocol.h"
#include <netdb.h>

typedef struct Response {
  t_buffer *buffer;
  uint16_t status_code;
} Response;

Response *response_create();
void response_send(Response *res, int socket);

#endif
