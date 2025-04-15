#include "http/protocol.h"
#include <http/client.h>
#include <http/response.h>
#include <stdio.h>

char *PORT = "3000";

int main(int argc, char *argv[]) {
  HttpClient *client = client_create();
  headers_add(client->headers, "Content-Type", "application/json");

  Body body = body_create();
  body_add_string(body, "{ \"id\": 1 }", 11);
  Response *res = client_send_post(client, body, "http://127.0.0.1:8080");
  body_destroy(body);

  printf("STATUS: %d\n", res->status_code);
  printf("HEADERS:\n");
  t_list_iterator *iterator = list_iterator_create(res->headers);
  while (list_iterator_has_next(iterator)) {
    Header *header = list_iterator_next(iterator);
    printf("%s: %s\n", header->key, header->value);
  }
  printf("BODY: %s\n", res->body->stream);

  client_destroy(client);

  return EXIT_SUCCESS;
}
