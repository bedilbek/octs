//
// Created by Tolqinbek Isoqov on 12/18/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *check_result(cJSON *request) {
    int user_id = (int) get_attr(request, "user_id", INTEGER);
    int contest_id = (int) get_attr(request, "contest_id", INTEGER);
    int problem_id = (int) get_attr(request, "problem_id", INTEGER);
    cJSON *response = get_successful_problem_results_in_contest(user_id, contest_id, problem_id);
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        setStatus(response, 200);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}