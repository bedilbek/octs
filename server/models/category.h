//
// Created by bedilbek on 12/9/17.
//

#ifndef OS_PROJECT_CATEGORY_H
#define OS_PROJECT_CATEGORY_H

#include "lib.h"

extern const void *Category;

struct Category {
    const void *class;
    cJSON *data;
};

cJSON *create_category_char(char *name, char *description);

cJSON *create_category_cJSON(cJSON *data);

cJSON *get_category_by_id(int category_id);

cJSON *get_all_categories();

cJSON *get_all_categories_count();

cJSON *get_category_by_problemId(int problem_id);

#endif //OS_PROJECT_CATEGORY_H
