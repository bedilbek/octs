#include "server_methods.h"
#include "model.h"

int validate(cJSON *data) {
    if (get_attr(data, "ext", STRING) != ".txt" | get_attr(data, "ext", STRING) != ".c") {
        return FALSE;
    }
    return TRUE;
}

cJSON *save_file(cJSON *data) {
    cJSON *response = cJSON_CreateObject();
    int is_valid = validate(data);
    if (!is_valid) {
        setStatus(response, 400);
        setErrMsg(response, "Not valid extension, it must be either .c or .txt");
        return response;
    }
    int user_id = (int) get_attr(data, "user_id", INTEGER);
    char *absolute_path = get_attr(data, "absolute_path", STRING);
    char ext[1024] = ".";
    strcat(ext, get_attr(data, "ext", STRING));
    response = create_file_char(user_id, absolute_path, ext);
    if ((int) get_attr(response, "status", INTEGER) != 701) {
        setStatus(response, 400);
        setErrMsg(response, "");
    } else {
        setStatus(response, 201);
        int file_id = (int) get_attr(cJSON_GetArrayItem(cJSON_GetObjectItem(response, "data"), 0), "id", INTEGER);
        free(response);
        response = cJSON_CreateObject();
        cJSON_AddNumberToObject(response, "file_id", file_id);
    }
    return response;
}
