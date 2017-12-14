//
// Created by Tolqinbek Isoqov on 12/9/17.
//

#ifndef OS_PROJECT_METHODS_H
#define OS_PROJECT_METHODS_H


#include "lib.h"

cJSON *login(cJSON *data);

cJSON *save_file(cJSON *data);

cJSON *signup(cJSON *data);

cJSON *get_contest_problems(cJSON *data);

cJSON *register_for_contest(cJSON *data);

cJSON *problem_details(cJSON *data);

#endif //OS_PROJECT_METHODS_H
