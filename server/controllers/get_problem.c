//
// Created by Tolqinbek Isoqov on 12/17/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *get_problem(cJSON *request) {
    int problem_id = (int) get_attr(request, "problem_id", INTEGER);
    cJSON *response = get_problem_by_id(problem_id);
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        setStatus(response, 200);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}