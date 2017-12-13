////
//// Created by Tolqinbek Isoqov on 12/9/17.
////

#include "model.h"
#include "methods.h"

cJSON *login(cJSON *data) {

    char *username = cJSON_GetObjectItem(data, "username")->valuestring;
    char *password = cJSON_GetObjectItem(data, "password")->valuestring;

    cJSON *response = cJSON_CreateObject();

    cJSON *user_query_result = exist_user(username, password);

    if (user_query_result->count == 1) {
        cJSON_AddStringToObject(response, "status", "200");
        cJSON_AddStringToObject(response, "token", "asdhjbeJFVElakdjkABDKBAlkjbdfasd=");

    } else {
        cJSON_AddStringToObject(response, "status", user_query_result->status);
    }

    return response;
}

