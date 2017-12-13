//
// Created by Tolqinbek Isoqov on 12/13/17.
//
#include "methods.h"
#include "model.h"

cJSON *get_contest_problems(cJSON *data) {
    int contest_id = cJSON_GetObjectItem(data, "contest_id")->valueint;
    printf("%d", contest_id);
    fflush(stdout);
    cJSON *response = get_problems_by_contest_id(contest_id, "DESC");
    return response;
}