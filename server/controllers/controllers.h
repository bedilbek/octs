//
// Created by Tolqinbek Isoqov on 12/9/17.
//

#ifndef OS_PROJECT_CONTROLLERS_H
#define OS_PROJECT_CONTROLLERS_H

#include "lib.h"
#include "server_methods.h"
#include "compiler.h"

typedef cJSON *(*function)(cJSON *);

const function methods[11] = {
        save_file,//Done
        login_server, //Done
        get_contest, //Done
        get_contests,//Done
        get_contest_problems,//Done
        get_problem,//Done
        signup,//Done
        register_for_contest,//Done
        users_contests,//Done
        problem_creation,//Done
        submit_problem,//-------
};
#endif //OS_PROJECT_CONTROLLERS_H
