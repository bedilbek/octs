//
// Created by bedilbek on 12/2/17.
//

#ifndef OS_PROJECT_DICTIONARY_H
#define OS_PROJECT_DICTIONARY_H

#include "helpers.h"

extern const void *Dict;

struct Dict {
    const void *class;
    char *key;
    char *value;
    cJSON *data;
};


#endif //OS_PROJECT_DICTIONARY_H
