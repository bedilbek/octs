//
// Created by Tolqinbek Isoqov on 12/17/17.
//
#include "server_methods.h"
#include "model.h"
#include <regex.h>

int validate_email(char *email) {
//    regex_t regex;
//    int match = regcomp(&regex, "\\w+([a-zA-Z0-9.])\\w+(@)([a-zA-Z])\\w+(.)([a-zA-Z])\\w+", 0);
//    if (match) {
//        printf("could not comple regex");
//    }
//    match = regexec(&regex, email, 0, NULL, 0);
//    if (!match)
//        return TRUE;
//    else
    return TRUE;
}


cJSON *signup(cJSON *request) {
    cJSON *response = cJSON_CreateObject();
    char *username = get_attr(request, "username", STRING);
    char *email = get_attr(request, "email", STRING);
    int is_valid = validate_email(email);
    if (!is_valid) {
        setStatus(response, 400);
        setErrMsg(response, "Email has wrong pattern");
        return response;
    }
    char *fname = get_attr(request, "fname", STRING);
    char *lname = get_attr(request, "lname", STRING);
    char *password = get_attr(request, "password", STRING);
    cJSON *validation = validate_user(username, email);
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