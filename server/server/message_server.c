//
// Created by Tolqinbek Isoqov on 12/12/17.
//

#include "server.h"
#include "controllers.h"
#include "model.h"

int authenticate_user(char *token) {
    cJSON *result_user = get_user_by_token(token);
    int user_id=0;
    if (!(user_id = (int) get_attr(cJSON_GetArrayItem(cJSON_GetObjectItem(result_user, "data"), 0), "id", INTEGER)))
        return 0;
    return user_id;
}

void return_response(int socket, cJSON *response) {
    char *response_message = cJSON_Print(response);
    send(socket, response_message, strlen(response_message), 0);
}

static void dispatch(struct Request *request) {
    printf(cJSON_Print(request->data));
    fflush(stdout);
    if (request->method != 1) {
        int user_id;
        if (!(user_id = authenticate_user((char *) request->token))) {
            cJSON *response = cJSON_CreateObject();
            setStatus(response, 403);
            setErrMsg(response, "Login in order to proceed operation");
            return_response(request->socket, response);
            close(request->socket);
            return;
        }
        if (get_attr(request->data, "user_id", INTEGER)) {
            cJSON_DetachItemFromObject(request->data, "user_id");
        }
        cJSON_AddNumberToObject(request->data, "user_id", user_id);
    }
    cJSON *response = methods[request->method](request->data);
    return_response(request->socket, response);
    close(request->socket);
}

struct Request make_request(int socket, int method, char *token, cJSON *data) {
    struct Request request = {};
    request.socket = socket;
    request.method = method;
    request.data = data;
    request.token = token;
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
    char *token = get_attr(message, "token", STRING);
    cJSON *params = get_attr(message, "params", CJSON);
    struct Request request = make_request(peer_socket, method, token, params);
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