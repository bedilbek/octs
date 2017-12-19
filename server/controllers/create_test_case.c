//
// Created by Tolqinbek Isoqov on 12/19/17.
//
#include "server_methods.h"
#include "model.h"


cJSON *create_test_case(cJSON *request) {
    cJSON *response = cJSON_CreateObject();
    int problem_id, input_file_id, output_file_id;
    char *explanation;
    if (!(problem_id = (int) get_attr(request, "problem_id", INTEGER))) {
        setStatus(response, 400);
        setErrMsg(response, "problem_id is required");
        return response;
    }
    if (!(input_file_id = (int) get_attr(request, "input_file_id", INTEGER))) {
        setStatus(response, 400);
        setErrMsg(response, "input_file_id is required");
        return response;
    }
    if (!(output_file_id = (int) get_attr(request, "output_file_id", INTEGER))) {
        setStatus(response, 400);
        setErrMsg(response, "input_file_id is required");
        return response;
    }
    if (!(explanation = get_attr(request, "explanation", STRING))) {
        setStatus(response, 400);
        setErrMsg(response, "explanation is required");
        return response;
    }
    response = create_test_case_char(problem_id, input_file_id, output_file_id, explanation, 1);
    if ((int) get_attr(response, "status", INTEGER) == 701) {
        setStatus(response, 201);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}
