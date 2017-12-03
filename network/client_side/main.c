//
// Created by Tolqinbek Isoqov on 12/3/17.
//
#include "client/client.c"


int main() {
    struct Client client = {};
    client = Client_ctor(client);
    cJSON *params = cJSON_CreateObject();
    cJSON_AddStringToObject(params, "name", "Tom");
    cJSON *response = (cJSON *) send_message(&client, "get_user", 0, params);
    printf(cJSON_Print(response));
}