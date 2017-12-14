//
// Created by Tolqinbek Isoqov on 12/12/17.
//

#include "server.h"
#include "controllers.h"

void return_response(int socket, cJSON *response) {
    char *response_message = cJSON_Print(response);
    send(socket, response_message, strlen(response_message), 0);
}

static void dispatch(struct Request *request) {
    printf(cJSON_Print(request->data));
    fflush(stdout);
    cJSON *response = methods[request->method](request->data);
    return_response(request->socket, response);
    close(request->socket);
}

struct Request make_request(int socket, int method, cJSON *data) {
    struct Request request = {};
    request.socket = socket;
    request.method = method;
    request.data = data;
    return request;
}

void pre_dispatch(int peer_socket) {
    char buffer[1024];
    pthread_t thread_id;
    int status = (int) read(peer_socket, buffer, MAX_LENGTH_OF_MESSAGE);
    if (status == 0) {
        return;
    }
    cJSON *message = cJSON_Parse(buffer);
    int method = (int) get_attr(message, "method", INTEGER);
    cJSON *params = get_attr(message, "params", CJSON);
    struct Request request = make_request(peer_socket, method, params);
    pthread_create(&thread_id, NULL, dispatch, &request);
}

void server_listen(struct Server *self) {
    while (TRUE) {
        int peer_socket;
        if ((peer_socket = accept(self->server_file_descriptor, (struct sockaddr *) &self->address,
                                  (socklen_t *) &self->addrlen)) < 0) {
            perror("accept");
        }
        pre_dispatch(peer_socket);
    }
}