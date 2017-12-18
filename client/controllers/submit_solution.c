//
// Created by Tolqinbek Isoqov on 12/15/17.
//

#include "client_methods.h"

void submit_solution(struct Client *file_client, struct Client *message_client, char *token, char *path, int contest_id,
                     int problem_id) {
    cJSON *response = send_file(file_client, token, path);
    int file_id;
    if ((int) get_attr(response, "status", INTEGER) != 201) {
        printf(get_attr(response, "err_msg", STRING));
    } else {
        file_id = (int) get_attr(response, "file_id", INTEGER);
        cJSON *request = cJSON_CreateObject();
        cJSON_AddNumberToObject(request, "contest_id", contest_id);
        cJSON_AddNumberToObject(request, "problem_id", problem_id);
        cJSON_AddNumberToObject(request, "file_id", file_id);
        response = send_message(message_client, token, SUBMIT_SOLUTION, request);
        if ((int) get_attr(response, "status", INTEGER) == 200) {
            printf("Solution is successfully submitted");
        } else {
            printf(get_attr(response, "err_msg", STRING));
        }
    }
}