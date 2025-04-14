#include "client.h"
#include "protocol.h"
#include "request.h"
#include "response.h"

HttpClient *client_create() {
  HttpClient *client = malloc(sizeof(HttpClient));
  client->headers = headers_create();
  return client;
}

void client_destroy(HttpClient *client) { headers_destroy(client->headers); }

Response *client_send(HttpClient *client, Method method, char *path,
                      Body body) {
  Request *req = request_create();
  req->headers = client->headers;
  req->body = body;
  //  req->method = method;
  request_send(req, path);
  // should open the connection first...
  //
  // maybe it is not the best to create the response here
  // client_wait or smth... ??
  Response *res = response_create();
  return res;
}

Response *client_send_get(HttpClient *client, Path path) {
  return client_send(client, "GET", path, NULL);
}

Response *client_send_post(HttpClient *client, Body body, Path path) {
  return client_send(client, "POST", path, body);
}

Response *client_send_put(HttpClient *client, Path path) {
  return client_send(client, "PUT", path, NULL);
}

Response *client_send_patch(HttpClient *client, Path path) {
  return client_send(client, "PATCH", path, NULL);
}

Response *client_send_delete(HttpClient *client, Path path) {
  return client_send(client, "DELETE", path, NULL);
}

Response *client_send_options(HttpClient *client, Path path) {
  return client_send(client, "OPTIONS", path, NULL);
}

Response *client_send_head(HttpClient *client, Path path) {
  return client_send(client, "HEAD", path, NULL);
}
