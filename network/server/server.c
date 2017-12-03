//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#include "server.h"

static void *Server_ctor(void *_self) {
    struct Server *self = _self;
    if ((self->server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Creating socket descriptor file is failed");
        exit(EXIT_FAILURE);
    }
    assert(self->server_file_descriptor);
    if (setsockopt(self->server_file_descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &self->opt,
                   sizeof(self->opt))) {
        perror("Failed setting pt of socket");
        exit(EXIT_FAILURE);
    }

    self->address.sin_family = AF_INET;
    self->address.sin_addr.s_addr = INADDR_ANY;
    self->address.sin_port = htons(PORT);
    assert(self->address.sin_family && self->address.sin_addr.s_addr && self->address.sin_port);

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