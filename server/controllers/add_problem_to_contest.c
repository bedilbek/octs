//
// Created by Tolqinbek Isoqov on 12/19/17.
//

#include "server_methods.h"
#include "model.h"

int validate_is_owner(int user_id, int contest_id) {
    cJSON *result = validate_contest_owner(user_id, contest_id);
    if ((int) get_attr(result, "count", INTEGER) > 0) {
        return TRUE;
    }
    return FALSE;
}

cJSON *add_problem_to_contest(cJSON *request) {
    cJSON *response = cJSON_CreateObject();
    int user_id = (int) get_attr(request, "user_id", INTEGER);
    int contest_id = (int) get_attr(request, "contest_id", INTEGER);
    int problem_id = (int) get_attr(request, "problem_id", INTEGER);
    if (!validate_is_owner(user_id, contest_id)) {
        setStatus(response, 400);
        setErrMsg(response, "You do not have access permission to this contest");
        return response;
    }
    response = create_contest_problem_char(contest_id, problem_id);
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        setStatus(response, 201);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}