//
// Created by Tolqinbek Isoqov on 12/13/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *get_contest_problems(cJSON *request) {
    //TODO: check if the contest started (showing problems is allowed)
    //TODO: check if the contest finished and problems can be shown without registration
    int user_id = (int) get_attr(request, "user_id", INTEGER);
    int contest_id;
    if (!(contest_id = (int) get_attr(request, "contest_id", INTEGER))) {
        return error_input("contest_id");
    }
    cJSON *response = get_problems_by_contest_id(contest_id, user_id, "ASC");
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        setStatus(response, 200);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "Error");
    }
    return response;
}