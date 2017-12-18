//
// Created by Tolqinbek Isoqov on 12/16/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *get_contests(cJSON *data) {
    cJSON *response = get_all_contests();
    int status;
    if ((status = (int) get_attr(response, "status", INTEGER)) == 700) {
        cJSON_DetachItemFromObject(response, "status");
        setStatus(response, 200);
        return response;
    } else {
        cJSON_DetachItemFromObject(response, "status");
        setStatus(response, 400);
        return response;
    }
}