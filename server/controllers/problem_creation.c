//
// Created by Tolqinbek Isoqov on 12/17/17.
//

#include "server_methods.h"
#include "model.h"

cJSON *problem_creation(cJSON *request) {
    int category_id = (int) get_attr(request, "category_id", INTEGER);
    char *title = get_attr(request, "title", STRING);
    char *description = get_attr(request, "description", STRING);
    int input_file_id = (int) get_attr(request, "input_file_id", INTEGER);
    int output_file_id = (int) get_attr(request, "output_file_id", INTEGER);
    int time_limit = (int) get_attr(request, "time_limit", INTEGER);
    int memory_limit = (int) get_attr(request, "memory_limit", INTEGER);
    int max_points = (int) get_attr(request, "max_points", INTEGER);
    cJSON *response = create_problem_char(category_id, description, input_file_id, output_file_id, time_limit,
                                          memory_limit, max_points, title);
    if ((int) get_attr(response, "status", INTEGER) == 701) {
        setStatus(response, 201);
    } else {
        setStatus(response, 400);
        setErrMsg(response, "");
    }
    return response;
}