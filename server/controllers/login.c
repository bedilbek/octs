////
//// Created by Tolqinbek Isoqov on 12/9/17.
////

#include "model.h"
#include "methods.h"

cJSON *login(cJSON *data) {

    char *username;
    char *password;
    if (!(username = get_attr(data, "username", STRING))) {
        return error_input("username");
    }
    if (!(password = get_attr(data, "password", STRING))) {
        return error_input("password");
    }


    cJSON *response = cJSON_CreateObject();

    cJSON *user_query_result = exist_user(username, password);

    if (cJSON_GetObjectItem(user_query_result, "count")->valueint == 1) {
        cJSON_AddStringToObject(response, "status", "200");
        cJSON_AddStringToObject(response, "token", "asdhjbeJFVElakdjkABDKBAlkjbdfasd=");

    } else {
        cJSON_AddStringToObject(response, "status", get_attr(user_query_result, "status", STRING));
    }

    return response;
}

