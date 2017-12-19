//
// Created by bedilbek on 12/7/17.
//

#ifndef OS_PROJECT_PROBLEM_H
#define OS_PROJECT_PROBLEM_H

#include "lib.h"

extern const void *Problem;

struct Problem {
    const void *class;
    cJSON *data;
    int id;
    int category_id;
    char *description;
    int input_format_file;
    int output_format_file;
    int time_limit;
    int memory_limit;
    int max_point;
    char title;
};

cJSON *create_problem_char(int category_id, char *description, int input_file_id,
                           int output_file_id, int time_limit, int memory_limit,
                           int max_points, char *title);

cJSON *create_problem_cJSON(cJSON *data);

cJSON *get_problem_by_id(int problem_id);

cJSON *get_all_problems();

cJSON *get_all_problems_count();

cJSON *get_problems_by_categoryId(int category_id);

void *map_problem(cJSON *from);

cJSON *validate_problem(int user_id, int problem_id);

#endif //OS_PROJECT_PROBLEM_H
