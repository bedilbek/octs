//
// Created by Tolqinbek Isoqov on 12/17/17.
//

#include "server_methods.h"
#include "model.h"

cJSON *get_contest(cJSON *request) {
    int contest_id = (int) get_attr(request, "contest_id", INTEGER);
    cJSON *response = get_contest_by_id(contest_id);
    printf(cJSON_Print(response));
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        setStatus(response, 200);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}