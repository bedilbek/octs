////
//// Created by Tolqinbek Isoqov on 12/9/17.
////

#include "model.h"
#include "server_methods.h"

cJSON *login_server(cJSON *data) {
    printf("login");
    char *username;
    char *password;
    if (!(username = get_attr(data, "username", STRING))) {
        return error_input("Username not found");
    }
    if (!(password = get_attr(data, "password", STRING))) {
        return error_input("Password not found");
    }
    cJSON *response = cJSON_CreateObject();

    cJSON *user_query_result = exist_user(username, password);

    if ((int) get_attr(user_query_result, "count", INTEGER) == 1) {
        setStatus(response, 200);
        char *token = get_attr(cJSON_GetArrayItem(get_attr(user_query_result, "data", CJSON), 0), "token", STRING);
        cJSON_AddStringToObject(response, "token", token);
    } else {
        setStatus(response, (int) get_attr(user_query_result, "status", INTEGER));
        setErrMsg(response, "User not found");
    }

    return response;
}

