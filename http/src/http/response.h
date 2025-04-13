#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "buffer.h"
#include "protocol.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *status[1000];

typedef struct Response {
  uint16_t status_code;
  Headers headers;
} Response;

Response *response_create();
void response_send(Response *res, int socket);
void response_destroy(Response *res);

#endif
