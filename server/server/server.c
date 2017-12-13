//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#include "lib.h"
#include "server.h"


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

static const struct Class _Server = {
        sizeof(struct Server),
        Server_ctor
};

const void *Server = &_Server;