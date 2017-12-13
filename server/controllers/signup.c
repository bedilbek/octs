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
        cJSON *query_result = create_user_char(fname, lname, username, hash_pswd(password), email);
        if (cJSON_GetObjectItem(query_result, status)->valuestring == "200") {
            setStatus(response, "200");
            setMessage(response, "User created.");
        } else {
            setStatus(response, cJSON_GetObjectItem(query_result, status)->valuestring);
            setErrMsg(response, cJSON_GetObjectItem(query_result, message)->valuestring);
            return response;
        }

        return response;
    } else {
        setStatus(response, "400");
        setErrMsg(response, "Please, enter valid info.");
        return response;
    }
}

bool valid_name(char *name) {
    if (strlen(name) > 0) {
        return true;
    } else {
        return false;
    }
}

bool valid_uname(char *uname) {
    if (strlen(uname) > 0 && cJSON_GetObjectItem(get_user_by_username(uname), "count")->valueint == 0) {
        return true;
    } else {
        return false;
    }
}

bool valid_pswd(char * pswd) {
    if (strlen(pswd) > 0) {
        return true;
    } else {
        return false;
    }
}

bool valid_email(char * email) {
    int email_adrs_len = strlen(email);
    int at_count = 0;
    int dot_count = 0;
    if (email_adrs_len > 5) {
        for (int i = 0; i < email_adrs_len; i++) {
            if (email[i] == '@') {
                at_count++;
            }
        }

        if (at_flag == 1) {
            for (int i = 0; i < email_adrs_len; i++) {
                if (email[i] == '.') {
                    dot_count++;
                }
            }

            if (dot_count != 0) {
                return true;
            } else {
                return false;
            }
        }
        else
            return false;
    } else {
        return false;
    }
}

char *hash_pswd(char *pswd) {
    return pswd;
}

