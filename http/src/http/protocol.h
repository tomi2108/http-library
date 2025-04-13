#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "list.h"
#include <string.h>

typedef char Method[8];
typedef char Path[1024];

typedef struct Header {
  char *key;
  char *value;
} Header;

typedef t_list *Headers;

Headers headers_create();
void headers_destroy(Headers headers);

void headers_add(Headers h, char *key, char *value);
char *headers_get(Headers h, char *key);

#endif
