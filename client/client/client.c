//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#include <fcntl.h>
#include "client.h"

cJSON *client_listen(struct Client *client) {
    char response[4096];
    read(client->sock, response, 4096);
    return cJSON_Parse(response);
}

static void *client_ctor(void *_self, va_list *arguments) {
    const int port = va_arg(*arguments, const int);
    struct Client *self = _self;
    self->sock = 0;
    if ((self->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Creating socket descriptor file is failed");
        exit(EXIT_FAILURE);
    }
    memset(&self->serv_addr, '0', sizeof(self->serv_addr));
    self->serv_addr.sin_family = AF_INET;
    self->serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, SERVER, &self->serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
    if (connect(self->sock, (struct sockaddr *) &self->serv_addr, sizeof(self->serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    return self;
}

static const struct Class _Client = {
        sizeof(struct Client),
        client_ctor
};

const void *Client = &_Client;
