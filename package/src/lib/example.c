#include "../include/server.h"
#include <stdio.h>

char *PORT = "3000";

void server_message() {
  printf("Server listening on port %s...", PORT);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  HttpServer *server = server_init();
  server_listen(server, PORT, &server_message);

  return EXIT_SUCCESS;
}
