////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "client.h"

int main() {
//    setbuf(stdout, NULL);
//    struct Client *client = new(Client, SERVER_LISTEN_PORT);
    struct Client *file_client = new(Client, FILE_SERVER_LISTEN_PORT);
//    cJSON *params = cJSON_CreateObject();
//    cJSON_AddNumberToObject(params, "user_id", 1);
//    cJSON_AddNumberToObject(params, "contest_id", 1);

//    cJSON *response = (cJSON *) send_message(client, "EDB34580-FDEE-4B46-8D58-98CD9B33EE05", 3, params);
    char path[] = "/Users/tom1/Documents/Subject files/OS/Project/octs/client/client/client.c";
    cJSON *response = (cJSON *) send_file(file_client, "EDB34580-FDEE-4B46-8D58-98CD9B33EE05", path);
    printf(cJSON_Print(response));
}