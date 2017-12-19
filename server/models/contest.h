//
// Created by bedilbek on 12/9/17.
//

#ifndef OS_PROJECT_CONTEST_H
#define OS_PROJECT_CONTEST_H

#include "lib.h"

extern const void *Contest;

struct Contest {
    const void *class;
    cJSON *data;
};

cJSON *create_contest_char(int author_id, char *starts_at, char *ends_at,
                           char *description, char *title,
                           char *reg_start_time, char *reg_end_time);

cJSON *create_contest_cJSON(cJSON *data);

cJSON *get_contest_by_id(int contest_id);

cJSON *get_all_contests();

cJSON *get_all_contests_count();

cJSON *get_contest_by_authorId(int author_id);

cJSON *validate_contest_owner(int user_id, int contest_id);

#endif //OS_PROJECT_CONTEST_H
