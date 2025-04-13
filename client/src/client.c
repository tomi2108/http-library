#include "http/protocol.h"
#include <http/client.h>
#include <http/response.h>

char *PORT = "3000";

int main(int argc, char *argv[]) {
  HttpClient *client = client_create();
  headers_add(client->headers, "x-app-id", "client_app");

  Response *res = client_send_get(client, "http://127.0.0.1:3000/hello");
  client_destroy(client);

  return EXIT_SUCCESS;
}
