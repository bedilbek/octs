//
// Created by ulugbekna on 12/13/17.
//

#include <stdbool.h>
#include "model.h"
#include "methods.h"

bool valid_name(char *);
bool valid_uname(char *);
bool valid_pswd(char *);
char *hash_pswd(char *);
bool valid_email(char *);

cJSON *signup(cJSON *data) {

    cJSON *response = cJSON_CreateObject();

    char *fname = cJSON_GetObjectItem(data, "fname")->valuestring;
    char *lname = cJSON_GetObjectItem(data, "lname")->valuestring;
    char *username = cJSON_GetObjectItem(data, "username")->valuestring;
    char *password = cJSON_GetObjectItem(data, "password")->valuestring;
    char *email = cJSON_GetObjectItem(data, "email")->valuestring;

    if (valid_name(fname) && valid_name(lname) && valid_uname(username) && valid_pswd(password) && valid_email(email)) {
        create_user_char(fname, lname, username, hash_pswd(password), email);
    } else {
        setStatus(response, "400");
        setErrMsg(response, "Please, enter valid info.");
    }

    create_user_char(fname, lname, username, password, email);

}

