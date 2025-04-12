#include <http/server.h>
#include <stdio.h>

char *PORT = "3000";

void hello_world_handler(Request *req, Response *res) {
  printf("Hello world");
  // should responses be created automatically by the server ??
  res = response_create();
  res->status_code = 200;
  // should responses be SENT automatically by the server ??
  //
  // res->sendable = false by default set to true if server should send ?
  // response_send(Response*)
  //
  // what if we want no response from the server, is
  // this even a realistic use case ? maybe send it to the next middleware...
  // provided we support middlewares someday
}

void server_message() {
  printf("Server listening on port %s...", PORT);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  HttpServer *server = server_create();

  server_endpoint(server, GET, "/hello", &hello_world_handler);
  server_listen(server, PORT, &server_message);

  return EXIT_SUCCESS;
}
