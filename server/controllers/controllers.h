//
// Created by Tolqinbek Isoqov on 12/9/17.
//

#ifndef OS_PROJECT_CONTROLLERS_H
#define OS_PROJECT_CONTROLLERS_H

#include "lib.h"
#include "server_methods.h"
#include "compiler.h"

typedef cJSON *(*function)(cJSON *);

const function methods[13] = {
        save_file,//Done, validate
        login_server, //Done
        get_contest, //Done
        get_contests,//Done
        get_contest_problems,//Done, validated
        get_problem_detail,//Done, validate
        signup,//Done, validate
        register_for_contest,//Done, validated
        users_contests,//Done
        problem_creation,//Done
        submit_problem,//Done
        check_result,//Done
        get_problems,//Done, validated
};
#endif //OS_PROJECT_CONTROLLERS_H
