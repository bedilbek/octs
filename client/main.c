////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "client.h"

int main() {
//    setbuf(stdout, NULL);
    struct Client *client = new(Client, SERVER_LISTEN_PORT);
//    struct Client *file_client = new(Client, FILE_SERVER_LISTEN_PORT);
    cJSON *params = cJSON_CreateObject();
    cJSON_AddNumberToObject(params, "user_id", 1);
    cJSON_AddNumberToObject(params, "contest_id", 3);

    cJSON *response = (cJSON *) send_message(client, 3, params);
//    cJSON *response = (cJSON *) send_file(file_client,
//                                          "/Users/tom1/Documents/Subject files/OS/Project/octs/client/client/client.c",
//                                          "client.c");
//    struct Client *client = new(Client, SERVER_LISTEN_PORT);
//    cJSON *params = cJSON_CreateObject();
//    cJSON_AddStringToObject(params, "name", "Tom");
//    cJSON *response = (cJSON *) send_message(client, 0, params);
    printf(cJSON_Print(response));
}