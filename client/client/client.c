//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#include "client.h"

static void *client_ctor(struct Client *_self) {
    struct Client *self = _self;
    self->sock = 0;
    if ((self->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Creating socket descriptor file is failed");
        exit(EXIT_FAILURE);
    }
    memset(&self->serv_addr, '0', sizeof(self->serv_addr));
    self->serv_addr.sin_family = AF_INET;
    self->serv_addr.sin_port = htons(CLIENT_SEND_PORT);

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

cJSON *client_listen(struct Client *client) {
    char response[1024];
    read(client->sock, response, 1024);
    return cJSON_Parse(response);
}

void *send_message(struct Client *client, char *method, cJSON *params) {
    cJSON *message = cJSON_CreateObject();
    cJSON_AddStringToObject(message, "method", method);
    cJSON_AddItemToObject(message, "params", params);
    char *message_rendered = cJSON_Print(message);
    int size = (int) send(client->sock, message_rendered, strlen(message_rendered), 0);
    if (size == 0) {
        exit(-1);
    }
    return client_listen(client);
}

static const struct Class _Client = {
        sizeof(struct Client),
        client_ctor
};

const void *Client = &_Client;
