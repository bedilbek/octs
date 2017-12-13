//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#include <pthread.h>
#include "server.h"
#include "controllers.h"

cJSON *get_attr(cJSON *data, char *field) {
    return cJSON_GetObjectItem(data, field);
}

void return_response(int socket, cJSON *response) {
    char *response_message = cJSON_Print(response);
    send(socket, response_message, strlen(response_message), 0);
}

struct Request make_request(int socket, int method, cJSON *data) {
    struct Request request = {};
    request.socket = socket;
    request.method = method;
    request.data = data;
    return request;
}

//// Server listen

static void dispatch(struct Request *request) {
    printf(cJSON_Print(request->data));
    fflush(stdout);
    cJSON *response = methods[request->method](request->data);
    return_response(request->socket, response);
    close(request->socket);
}

void pre_dispatch(int peer_socket) {
    char buffer[1024];
    pthread_t thread_id;
    int status = (int) read(peer_socket, buffer, MAX_LENGTH_OF_MESSAGE);
    if (status == 0) {
        return;
    }
    cJSON *message = cJSON_Parse(buffer);
    int method = get_attr(message, "method")->valueint;
    cJSON *params = get_attr(message, "params");
    struct Request request = make_request(peer_socket, method, params);
    pthread_create(&thread_id, NULL, dispatch, &request);
}

static void *Server_ctor(void *_self, va_list *arguments) {
    const char *port = va_arg(*arguments, const char *);
    struct Server *self = _self;
    self->opt = 1;
    self->addrlen = sizeof(struct sockaddr_in);

    if ((self->server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Creating socket descriptor file is failed");
        exit(EXIT_FAILURE);
    }
    assert(self->server_file_descriptor);
    if (setsockopt(self->server_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &self->opt,
                   sizeof(int))) {
        perror("Failed setting pt of socket");
        exit(EXIT_FAILURE);
    }

    self->address.sin_family = AF_INET;
    self->address.sin_addr.s_addr = INADDR_ANY;
    self->address.sin_port = htons(port);
//    assert(self.address.sin_family & self.address.sin_addr.s_addr & self.address.sin_port);

    if (bind(self->server_file_descriptor, (struct sockaddr *) &self->address, sizeof(self->address)) < 0) {
        perror("Failed binding port");
        exit(EXIT_FAILURE);
    }

    if (listen(self->server_file_descriptor, MAX_NUM_CLIENT) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    return self;
}

void server_listen(struct Server *self) {
    while (TRUE) {
        printf("listen server");
        int peer_socket;
        if ((peer_socket = accept(self->server_file_descriptor, (struct sockaddr *) &self->address,
                                  (socklen_t *) &self->addrlen)) < 0) {
            perror("accept");
        }
        pre_dispatch(peer_socket);
    }
}

//// File server listen

char *get_full_path(char *file_name) {
    //TODO: make file management
    return strcat("/media/files/", file_name);
}

void receive_file(int peer_socket) {
    //init variables
    int len;
    int file_size = 0;
    FILE *received_file;
    char buffer[MAX_LENGTH_OF_MESSAGE];

    recv(peer_socket, buffer, MAX_LENGTH_OF_MESSAGE, 0); ////receive metadata about coming file

    //separate request into datum
    cJSON *message = cJSON_Parse(buffer);
    cJSON *token = get_attr(message, "token");
    cJSON *length = get_attr(message, "length");
    cJSON *file_name = get_attr(message, "file_name");

    //Create file
    file_size = length->valueint;
    const char *absolute_file_path = get_full_path(file_name->valuestring);
    received_file = fopen(absolute_file_path, "w");
    if (received_file == NULL) {
        fprintf(stderr, "Failed to open file of user with token \"%s\"", token->valuestring);
        return;
    }

    while (((len = (int) recv(peer_socket, buffer, MAX_LENGTH_OF_MESSAGE, 0)) > 0) && (file_size > 0)) {
        fwrite(buffer, sizeof(char), len, received_file);
        file_size -= len;
    }
    fclose(received_file);
    cJSON_AddStringToObject(message, "file", absolute_file_path);
    cJSON *response = methods[1](message);
    return_response(peer_socket, response);
    close(peer_socket);
}

void file_server_listen(struct Server *self) {
    while (TRUE) {
        printf("listen file server");
        int peer_socket;
        pthread_t pid;
        if ((peer_socket = accept(self->server_file_descriptor, (struct sockaddr *) &self->address,
                                  (socklen_t *) &self->addrlen)) < 0) {
            perror("accept");
        }
        pthread_create(&pid, NULL, (void *) receive_file, (void *) peer_socket);
        receive_file(peer_socket);
    }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static const struct Class _Server = {
        sizeof(struct Server),
        Server_ctor
};

const void *Server = &_Server;