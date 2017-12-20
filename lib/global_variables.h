//
// Created by Tolqinbek Isoqov on 12/20/17.
//

#ifndef OS_PROJECT_GLOBAL_VARIABLES_H
#define OS_PROJECT_GLOBAL_VARIABLES_H

#include "lib.h"

int temp_file_name_counter = 0;
int temp_is_locked = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#endif //OS_PROJECT_GLOBAL_VARIABLES_H
