//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#include "client.h"

static struct Client Client_ctor(struct Client self) {
    self.sock = 0;
    if ((self.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Creating socket descriptor file is failed");
        exit(EXIT_FAILURE);
    }
    memset(&self.serv_addr, '0', sizeof(self.serv_addr));
    self.serv_addr.sin_family = AF_INET;
    self.serv_addr.sin_port = htons(CLIENT_SEND_PORT);

    if (inet_pton(AF_INET, SERVER, &self.serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
    if (connect(self.sock, (struct sockaddr *) &self.serv_addr, sizeof(self.serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
    return self;
}

static cJSON *client_listen() {
    return cJSON_CreateObject();
}

static void *send_message(struct Client *client, char *method, int response, cJSON *params) {
    cJSON *message = cJSON_CreateObject();
    cJSON_AddStringToObject(message, "method", method);
    cJSON_AddBoolToObject(message, "response", response);
    cJSON_AddItemToObject(message, "params", params);
    char *message_rendered = cJSON_Print(message);
    int size = send(client->sock, message_rendered, strlen(message_rendered), 0);
    if (response) {
        return client_listen();
    }
    cJSON *default_response = cJSON_CreateObject();
    cJSON_AddStringToObject(default_response, "message", "Successfully sent");
    return default_response;
}
