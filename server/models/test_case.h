//
// Created by bedilbek on 12/10/17.
//

#ifndef OS_PROJECT_TEST_CASE_H
#define OS_PROJECT_TEST_CASE_H

#include "lib.h"
#include "model.h"

extern const void *TestCase;

struct TestCase {
    const void *class;
    cJSON *data;
    int id;
    int problem_id;
    char *input_file_path;
    char *output_file_path;
    char *explanation;
    bool is_sample;
};

 int map_test_case(cJSON *from, struct TestCase **to);

cJSON *create_test_case_char(int problem_id, int input_file_id, int output_file_id,
                             char *explanation, int is_sample);

cJSON *create_test_case_cJSON(cJSON *data);

cJSON *get_test_cases_of_problem(int problem_id);

cJSON *get_sample_test_cases_of_problem(int problem_id);

cJSON *get_test_case_by_id(int test_case_id);

#endif //OS_PROJECT_TEST_CASE_H
