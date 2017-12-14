//
// Created by bedilbek on 12/9/17.
//

#ifndef OS_PROJECT_CONTEST_PROBLEM_H
#define OS_PROJECT_CONTEST_PROBLEM_H

#include "lib.h"

extern const void *ContestProblem;

struct ContestProblem {
    const void *class;
    cJSON *data;
};

cJSON *create_contest_problem_char(int contest_id, int problem_id);

cJSON *create_contest_problem_cJSON(cJSON *data);

cJSON *get_contests_by_problem_id(int problem_id);

cJSON *get_problems_by_contest_id(int contest_id, char *order);

cJSON *get_all_problems_count_by_contests();

cJSON *get_problems_count_by_contest_id(int contest_id);

#endif //OS_PROJECT_CONTEST_PROBLEM_H
