//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#include "server.h"

cJSON *get_attr(cJSON *data, char *field) {
    return cJSON_GetObjectItem(data, field);
}

static void dispatch(int socket) {
    char *buffer[1024];
    int status = read(socket, buffer, LENGTH_OF_MESSAGE);
    if (status == 0) {
        exit(-1);
    }
    cJSON *message = cJSON_Parse(buffer);
    int response = get_attr(message, "response")->valueint;
    char *method = get_attr(message, "method")->valuestring;
    cJSON *params = get_attr(message, "params");

    fflush(stdout);
}

static struct Server Server_ctor(struct Server self) {
    self.opt = 1;
    self.addrlen = sizeof(self.address);

    if ((self.server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Creating socket descriptor file is failed");
        exit(EXIT_FAILURE);
    }
    assert(self.server_file_descriptor);
    if (setsockopt(self.server_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &self.opt,
                   sizeof(self.opt))) {
        perror("Failed setting pt of socket");
        exit(EXIT_FAILURE);
    }

    self.address.sin_family = AF_INET;
    self.address.sin_addr.s_addr = INADDR_ANY;
    self.address.sin_port = htons(SERVER_LISTEN_PORT);
//    assert(self.address.sin_family & self.address.sin_addr.s_addr & self.address.sin_port);

    if (bind(self.server_file_descriptor, (struct sockaddr *) &self.address, sizeof(self.address)) < 0) {
        perror("Failed binding port");
        exit(EXIT_FAILURE);
    }

    if (listen(self.server_file_descriptor, MAX_NUM_CLIENT) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    return self;
}

void server_listen(struct Server self) {
    while (TRUE) {
        int new_socket;
        if ((new_socket = accept(self.server_file_descriptor, (struct sockaddr *) &self.address,
                                 (socklen_t *) &self.addrlen)) < 0) {
            perror("accept");
        }
        dispatch(new_socket);
    }
}