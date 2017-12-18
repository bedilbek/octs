//
// Created by Sherzod on 12/14/17.
//

#ifndef OS_PROJECT_COMPILER_H
#define OS_PROJECT_COMPILER_H

#include "lib.h"
#include <stdlib.h>
#include <time.h>
#include "model.h"

#define TEST_CASE_OK 800
#define COMPILATION_ERROR 801
#define TEST_CASE_FAILED 802
#define TEST_CASES_SUCCESS 803
#define TEST_CASES_UNDEFINED_ERROR 804
#define TEST_CASE_TIME_LIMIT 805

int compare_outputs(FILE *actual, FILE *expected);
char *get_temp_file_name();
char *get_temp_location();
//1 if error otherwise 0
int if_error(char *error_file);
int execute(char *code_path, struct TestCase testCase, int time_limit);
void compile(char *code_path, int user_id, int contest_id, int problem_id);
#endif //OS_PROJECT_COMPILER_H