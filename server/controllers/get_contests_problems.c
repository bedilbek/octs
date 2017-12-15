//
// Created by Tolqinbek Isoqov on 12/13/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *get_contest_problems(cJSON *data) {
    //TODO: check if the contest started (showing problems is allowed)
    //TODO: check if the contest finished and problems can be shown without registration
    int contest_id;
    if (!(contest_id= (int) get_attr(data, "contest_id", INTEGER))) {
        return error_input("contest_id");
    }
    cJSON *response = get_problems_by_contest_id(contest_id, "DESC");
    return response;
}