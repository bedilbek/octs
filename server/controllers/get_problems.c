//
// Created by Tolqinbek Isoqov on 12/19/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *get_problems(cJSON *request) {
    cJSON *response = get_all_problems();
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        setStatus(response, 200);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}