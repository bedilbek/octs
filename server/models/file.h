//
// Created by bedilbek on 12/14/17.
//

#ifndef OS_PROJECT_FILE_H
#define OS_PROJECT_FILE_H

#include "lib.h"

extern const void *File;

struct File {
    const void *class;
    cJSON *data;
};

cJSON *create_file_char(int user_id, char *path, char *ext);

cJSON *create_file_cJSON(cJSON *data);

cJSON *get_file_by_path(char *file_path);

cJSON *get_file_by_id(int file_id);

cJSON *get_files_of_user(int user_id);

#endif //OS_PROJECT_FILE_H
