//
// Created by Tolqinbek Isoqov on 12/18/17.
//
#include <pthread.h>
#include "server_methods.h"
#include "model.h"
#include "compiler.h"

int validate_participant(int user_id, int contest_id, int problem_id) {
    cJSON *user_contest_result = validate_user_contest_result(user_id, contest_id, problem_id);
    if ((int) get_attr(user_contest_result, "count", INTEGER) > 0) {
        return TRUE;
    }
    return FALSE;
}

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
    cJSON *response = cJSON_CreateObject();
    int user_id = (int) get_attr(request, "user_id", INTEGER), contest_id, problem_id;
    if (!(contest_id = (int) get_attr(request, "contest_id", INTEGER))) {
        setStatus(response, 400);
        setErrMsg(response, "contest_id is required");
        return response;
    }
    if (!(problem_id = (int) get_attr(request, "problem_id", INTEGER))) {
        setStatus(response, 400);
        setErrMsg(response, "problem_id is required");
        return response;
    }
    int valid_participant = validate_participant(user_id, contest_id, problem_id);
    if (!valid_participant) {
        setStatus(response, 400);
        setErrMsg(response, "You are not registered for this contest");
        return response;
    }
    pthread_t tid;
    pthread_create(&tid, NULL, execute_solution, request);
    printf("User with id %d submit solution to contest's (%d) problem with id %d", user_id, contest_id, problem_id);
    setStatus(response, 200);
    return response;
}