//
// Created by Tolqinbek Isoqov on 12/17/17.
//
#include "server_methods.h"
#include "model.h"

int validate_access(int user_id, int problem_id) {
    cJSON *contest_problems = get_contests_by_problem_id(problem_id);
    if ((int) get_attr(contest_problems, "count", INTEGER) > 0) {
        contest_problems = validate_problem(user_id, problem_id);
        if ((int) get_attr(contest_problems, "count", INTEGER) > 0) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

cJSON *get_problem_detail(cJSON *request) {
    cJSON *response = cJSON_CreateObject();
    int user_id = (int) get_attr(request, "user_id", INTEGER);
    int problem_id = (int) get_attr(request, "problem_id", INTEGER);
    int has_access = validate_access(user_id, problem_id);
    if (!has_access) {
        setStatus(response, 400);
        setErrMsg(response, "You can not see contest problems");
        return response;
    }
    response = get_problem_by_id(problem_id);
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        setStatus(response, 200);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}