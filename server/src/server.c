#include <http/protocol.h>
#include <http/server.h>
#include <stdio.h>

char *PORT = "8080";

void hello_world_get_handler(Request *req, Response *res) {
  res->status_code = 503;
}

void hello_world_post_handler(Request *req, Response *res) {
  res->status_code = 200;
  headers_add(res->headers, "Content-Type", "text/html; charset=utf-8");
}

void server_message() {
  printf("Server listening on port %s...\n", PORT);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  HttpServer *server = server_create();

  server_get(server, "/hello", &hello_world_get_handler);
  server_post(server, "/hello", &hello_world_post_handler);
  server_listen(server, PORT, &server_message);

  return EXIT_SUCCESS;
}
