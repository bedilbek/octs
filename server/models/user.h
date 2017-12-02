//
// Created by bedilbek on 12/5/17.
//

#ifndef OS_PROJECT_USER_H
#define OS_PROJECT_USER_H

#include "lib.h"
#include "cJSON.h"

extern const void *User;

struct User {
    const void *class;
    cJSON *data;
};

cJSON *create_user_char(char *fname, char *lname, char *username, char *password, char *email);

cJSON *create_user_cJSON(cJSON *data);

cJSON *get_user_by_id(int user_id);

cJSON *get_user_by_username(char *username);

cJSON *exist_user(char *username, char *password);

cJSON *get_all_users();

cJSON *get_all_users_count();

#define create_user(_1, ...) _Generic((_1),                                  \
                              char*: _Generic((FIRST(__VA_ARGS__,)), \
                                     char*: create_user_char))(_1, __VA_ARGS__),\
                              cJSON*: create_user_cJSON

#define FIRST(A, ...) A


#endif //OS_PROJECT_USER_H
