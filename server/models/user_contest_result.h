//
// Created by bedilbek on 12/10/17.
//

#ifndef OS_PROJECT_USER_CONTEST_RESULT_H
#define OS_PROJECT_USER_CONTEST_RESULT_H

#include "lib.h"

extern const void *UserContestResult;

struct UserContestResult {
    const void *class;
    cJSON *data;
};

cJSON *create_user_contest_result_char(int user_id, int contest_id, int total_points);

cJSON *create_user_contest_result_cJSON(cJSON *data);

cJSON *get_participants_from_contest(int contest_id);

cJSON *get_contests_of_user(int user_id);

cJSON *get_user_contest_result(int user_id, int contest_id);

#endif //OS_PROJECT_USER_CONTEST_RESULT_H
