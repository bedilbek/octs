//
// Created by Tolqinbek Isoqov on 12/14/17.
//

#include "methods.h"
#include "model.h"

cJSON *users_contests(cJSON *data) {
    int user_id = (int) get_attr(data, "user_id", INTEGER);
    cJSON *response = get_contests_of_user(user_id);
    return response;
}

