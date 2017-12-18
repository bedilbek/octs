//
// Created by Tolqinbek Isoqov on 12/18/17.
//
#include "server_methods.h"
#include "model.h"

void execute_program(int result) {

}

cJSON *submit_problem(cJSON *request) {
    int user_id = (int) get_attr(request, "user_id", INTEGER);
    int contest_id = (int) get_attr(request, "contest_id", INTEGER);
    int problem_id = (int) get_attr(request, "problem_id", INTEGER);
    create_problem_result_char()
}