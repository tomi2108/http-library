#include <http/client.h>

char *PORT = "3000";

int main(int argc, char *argv[]) {
  HttpClient *client = client_create();

  client_send(client, GET, "http://127.0.0.1:3000/hello");

  return EXIT_SUCCESS;
}
