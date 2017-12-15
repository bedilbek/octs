//
// Created by Tolqinbek Isoqov on 12/14/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *problem_details(cJSON *data) {
    int problem_id;
    if (!(problem_id = (int) get_attr(data, "problem_id", INTEGER))) {
        cJSON *response = cJSON_CreateObject();
        setStatus(response, 400);
        setErrMsg(response, "problem_id is required");
    }
    cJSON *response = get_problem_by_id(problem_id);
    return response;
}