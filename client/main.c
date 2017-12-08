//
// Created by Tolqinbek Isoqov on 12/3/17.
//
#include "client.h"

int main() {
    struct Client *client = new(Client);
    cJSON *params = cJSON_CreateObject();
    cJSON_AddStringToObject(params, "name", "Tom");
    cJSON *response = (cJSON *) send_message(client, "get_user", params);
    printf(cJSON_Print(response));
}