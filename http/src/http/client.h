#ifndef CLIENT_H_
#define CLIENT_H_

#include "buffer.h"
#include "list.h"
#include "request.h"
#include "response.h"
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct HttpClient {
} HttpClient;

HttpClient *client_create();
Response *client_send(HttpClient *client, char method[8], char *path);

#endif
