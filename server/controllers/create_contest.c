//
// Created by Tolqinbek Isoqov on 12/19/17.
//

#include "server_methods.h"
#include "model.h"

cJSON *create_contest(cJSON *request) {
    int user_id = (int) get_attr(request, "user_id", INTEGER);
    char *title = get_attr(request, "title", STRING);
    char *description = get_attr(request, "description", STRING);
    char *starts_at = get_attr(request, "starts_at", STRING);
    char *ends_at = get_attr(request, "ends_at", STRING);
    char *reg_start_time = get_attr(request, "reg_start_time", STRING);
    char *reg_end_time = get_attr(request, "reg_end_time", STRING);
    cJSON *response = create_contest_char(user_id, starts_at, ends_at, description, title, reg_start_time,
                                          reg_end_time);
    if ((int) get_attr(response, "status", INTEGER) == 700) {
        printf("Contest is created by user %d", user_id);
        setStatus(response, 201);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}