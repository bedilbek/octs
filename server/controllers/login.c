////
//// Created by Tolqinbek Isoqov on 12/9/17.
////

#include "methods.h"

cJSON *login(cJSON *data) {
    cJSON *response = cJSON_CreateObject();
    cJSON_AddStringToObject(response, "token", "asdhjbeJFVElakdjkABDKBAlkjbdfasd=");
    return response;
}

