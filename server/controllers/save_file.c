#include "methods.h"

cJSON *save_file(cJSON *data) {
    cJSON *response = cJSON_CreateObject();
    cJSON_AddNumberToObject(response, "status", 201);
    return response;
}