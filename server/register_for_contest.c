//
// Created by Tolqinbek Isoqov on 12/14/17.
//
#include "methods.h"
#include "model.h"

cJSON *register_for_contest(cJSON *data) {
    int user_id = (int) get_attr(data, "user_id", INTEGER);
    int contest_id;
    if (!(contest_id = (int) get_attr(data, "contest_id", INTEGER))) {
        return error_input("contest_id");
    }
    cJSON *response = create_user_contest_result_char(user_id, contest_id, 0);
    if ((int) get_attr(response, "status", INTEGER) == 201) {
        return response;
    }
    if ((int) get_attr(response, "status", INTEGER) == 506) {
        response = cJSON_CreateObject();
        setStatus(response, 400);
        setErrMsg(response,"contest_id is not valid");
    }
    return response;
}