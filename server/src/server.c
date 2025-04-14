#include "http/list.h"
#include <http/protocol.h>
#include <http/server.h>
#include <stdio.h>

char *PORT = "8080";

void hello_world_get_handler(Request *req, Response *res) {
  res->status_code = 200;
  headers_add(res->headers, "Content-Type", "text/html; charset=utf-8");

  t_list_iterator *iterator = list_iterator_create(req->headers);
  while (list_iterator_has_next(iterator)) {
    Header *header = list_iterator_next(iterator);
    printf("%s: %s\n", header->key, header->value);
    fflush(stdout);
  }

}

void server_message() {
  printf("Server listening on port %s...\n", PORT);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  HttpServer *server = server_create();

  server_get(server, "/hello", &hello_world_get_handler);
  server_listen(server, PORT, &server_message);

  return EXIT_SUCCESS;
}
