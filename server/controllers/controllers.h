//
// Created by Tolqinbek Isoqov on 12/9/17.
//

#ifndef OS_PROJECT_CONTROLLERS_H
#define OS_PROJECT_CONTROLLERS_H

#include "lib.h"
#include "methods.h"

typedef cJSON *(*function)(cJSON *);

const function methods[10] = {
        login,
        save_file,
};
#endif //OS_PROJECT_CONTROLLERS_H
