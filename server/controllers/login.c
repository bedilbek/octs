////
//// Created by Tolqinbek Isoqov on 12/9/17.
////

#include "model.h"
#include "methods.h"

cJSON *login(cJSON *data) {
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
        cJSON_AddStringToObject(response, "token", "asdhjbeJFVElakdjkABDKBAlkjbdfasd=");
    } else {
        setStatus(response, get_attr(user_query_result, "status", STRING));
        setErrMsg(response, "User not found");
    }

    return response;
}

