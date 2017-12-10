//
// Created by bedilbek on 12/10/17.
//

#ifndef OS_PROJECT_PROBLEM_RESULT_H
#define OS_PROJECT_PROBLEM_RESULT_H

#include "lib.h"

extern const void *ProblemResult;

struct ProblemResult {
    const void *class;
    cJSON *data;
};

cJSON *create_problem_result_char(int user_id, int contest_id, int problem_id,
                                  int points, int success, void *failed_test_case_id);

cJSON *create_problem_result_cJSON(cJSON *data);

cJSON *get_problem_results_in_contest(int user_id, int contest_id);

cJSON *get_problem_result_trials_in_contest(int user_id, int contest_id, int problem_id);

cJSON *get_successful_problem_results_in_contest(int user_id, int contest_id);

cJSON *get_successful_problem_result_in_contest(int user_id, int contest_id, int problem_id);

cJSON *get_all_problem_results_count_in_contest(int user_id, int contest_id);

cJSON *get_all_participants_in_contest(int contest_id);

#endif //OS_PROJECT_PROBLEM_RESULT_H
