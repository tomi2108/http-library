#include "client.h"
#include "request.h"
#include "response.h"

HttpClient *client_create() {
  HttpClient *client = malloc(sizeof(HttpClient));
  return client;
}

Response *client_send(HttpClient *client, Method method, char *path) {
  Request *req = request_create();
  req->method = method;
  request_send(req, path);
  // should open the connection first...
  //
  // maybe it is not the best to create the response here
  // client_wait or smth... ??
  Response *res = response_create();
  return res;
}
