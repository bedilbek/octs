//
// Created by Tolqinbek Isoqov on 12/16/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *get_contests(cJSON *data) {
    printf("get contest");
    cJSON *response = get_all_contests();
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        cJSON_DetachItemFromObject(response, "status");
        setStatus(response, 200);
    } else {
        cJSON_DetachItemFromObject(response, "status");
        setStatus(response, 400);
    }
    printf(cJSON_Print(response));
    return response;
}