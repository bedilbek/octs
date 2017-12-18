#include "server_methods.h"
#include "model.h"

cJSON *save_file(cJSON *data) {
    int user_id = (int) get_attr(data, "user_id", INTEGER);
    char *absolute_path = get_attr(data, "absolute_path", STRING);
    char ext[1024] = ".";
    strcat(ext, get_attr(data, "ext", STRING));
    cJSON *response = create_file_char(user_id, absolute_path, ext);
    printf(cJSON_Print(response));
    int file_id = (int) get_attr(cJSON_GetArrayItem(cJSON_GetObjectItem(response, "data"), 0), "id", INTEGER);
    free(response);
    response = cJSON_CreateObject();
    setStatus(response, 201);
    cJSON_AddNumberToObject(response, "file_id", file_id);
    return response;
}