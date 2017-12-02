//
// Created by bedilbek on 12/2/17.
//

#ifndef OS_PROJECT_STRING_H
#define OS_PROJECT_STRING_H

#include "../helpers.h"

extern const void *String;

struct String {
    const void *class;
    cJSON *data;
};

#endif //OS_PROJECT_STRING_H
