//
// Created by Tolqinbek Isoqov on 12/14/17.
//
#include "server_methods.h"
#include "model.h"

cJSON *register_for_contest(cJSON *data) {
    cJSON *response = cJSON_CreateObject();
    int user_id = (int) get_attr(data, "user_id", INTEGER);
    int contest_id;
    if (!(contest_id = (int) get_attr(data, "contest_id", INTEGER))) {
        return error_input("contest_id");
    }
    cJSON *is_registered = get_user_contest_result(user_id, contest_id);
    if ((int) get_attr(is_registered, "count", INTEGER) > 0) {
        setStatus(response, 400);
        setErrMsg(response, "You have already registered");
        return response;
    }
    response = create_user_contest_result_char(user_id, contest_id, 0);
    if ((int) get_attr(response, "status", INTEGER) == 701) {
        setStatus(response, 201);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }

    return response;
}