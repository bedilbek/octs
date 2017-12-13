////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "client.h"

int main() {
    struct Client *client = new(Client, SERVER_LISTEN_PORT);
    cJSON *params = cJSON_CreateObject();
    cJSON_AddStringToObject(params, "name", "Tom");
    cJSON *response = (cJSON *) send_message(client, 0, params);
    printf(cJSON_Print(response));
}