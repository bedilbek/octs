//
// Created by Tolqinbek Isoqov on 12/18/17.
//
#include <pthread.h>
#include "server_methods.h"
#include "model.h"
#include "compiler.h"

void execute_solution(cJSON *params) {
    int user_id = (int) get_attr(params, "user_id", INTEGER);
    int contest_id = (int) get_attr(params, "contest_id", INTEGER);
    int problem_id = (int) get_attr(params, "problem_id", INTEGER);
    int file_id = (int) get_attr(params, "file_id", INTEGER);
    cJSON *file = get_file_by_id(file_id);
    char *file_path = get_attr(cJSON_GetArrayItem(get_attr(file, "data", CJSON), 0), "path", STRING);
    compile(file_path, user_id, contest_id, problem_id);
}

cJSON *submit_problem(cJSON *request) {
    pthread_t tid;
    printf("submit solution");
    pthread_create(&tid, NULL, execute_solution, request);
    cJSON *response = cJSON_CreateObject();
    setStatus(response, 200);
    return response;
}