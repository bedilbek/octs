//
// Created by Tolqinbek Isoqov on 12/12/17.
//

#include "client.h"

void *send_message(struct Client *client, char *token, int method, cJSON *params) {
    cJSON *message = cJSON_CreateObject();
    cJSON_AddNumberToObject(message, "method", method);
    cJSON_AddStringToObject(message, "token", token);
    cJSON_AddItemToObject(message, "params", params);
    char *message_rendered = cJSON_Print(message);
    int size = (int) send(client->sock, message_rendered, strlen(message_rendered), 0);
    if (size == 0) {
        exit(-1);
    }
    return client_listen(client);
}