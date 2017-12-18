//
// Created by Tolqinbek Isoqov on 12/17/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *signup(cJSON *request) {
    char *fname = get_attr(request, "fname", STRING);
    char *lname = get_attr(request, "lname", STRING);
    char *username = get_attr(request, "username", STRING);
    char *email = get_attr(request, "email", STRING);
    char *password = get_attr(request, "password", STRING);
    cJSON *validation = validate_user(username, email);
    cJSON *response = cJSON_CreateObject();
    if ((int) get_attr(validation, "count", INTEGER) > 0) {
        setStatus(response, 400);
        setErrMsg(response, "User with username or password exists. Please try with other credentials");
        return response;
    }
    cJSON *user = create_user_char(fname, lname, username, password, email, generate_token());
    if ((int) get_attr(user, "status", INTEGER) == 700) {
        setStatus(response, 201);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}