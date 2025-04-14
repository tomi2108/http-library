#include "http/protocol.h"
#include <http/client.h>
#include <http/response.h>

char *PORT = "3000";

int main(int argc, char *argv[]) {
  HttpClient *client = client_create();
  headers_add(client->headers, "Content-Type", "application/json");

  Body body = body_create();
  body_add_string(body, "{ \"id\": 1 }", 11);
  Response *res = client_send_post(client, body, "http://127.0.0.1:3000/hello");
  body_destroy(body);

  client_destroy(client);

  return EXIT_SUCCESS;
}
