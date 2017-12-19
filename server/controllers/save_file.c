#include "server_methods.h"
#include "model.h"

int validate(cJSON *data) {
//    if ((char *) get_attr(data, "ext", STRING) != "txt" || (char *) get_attr(data, "ext", STRING) != "c") {
//        return FALSE;
//    }
    return TRUE;
}

cJSON *save_file(cJSON *data) {
    cJSON *response;
//    int is_valid = validate(data);
//    if (!is_valid) {
//        setStatus(response, 400);
//        setErrMsg(response, "Not valid extension, it must be either .c or .txt");
//        return response;
//    }
    int user_id = (int) get_attr(data, "user_id", INTEGER);
    char *absolute_path = get_attr(data, "absolute_path", STRING);
    char ext[1024] = ".";
    strcat(ext, get_attr(data, "ext", STRING));
    response = create_file_char(user_id, absolute_path, ext);
    printf(cJSON_Print(response));
    if ((int) get_attr(response, "status", INTEGER) != 700) {
        setStatus(response, 400);
        setErrMsg(response, "");
    } else {
        int file_id = (int) get_attr(cJSON_GetArrayItem(cJSON_GetObjectItem(response, "data"), 0), "id", INTEGER);
        free(response);
        response = cJSON_CreateObject();
        setStatus(response, 201);
        cJSON_AddNumberToObject(response, "file_id", file_id);
    }
    printf(cJSON_Print(response));
    return response;
}
