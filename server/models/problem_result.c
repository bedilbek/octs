//
// Created by bedilbek on 12/10/17.
//

#include "problem_result.h"

#define PROBLEM_RESULT_CLONE 2

#define PROBLEM_RESULT_ID "id"
#define PROBLEM_RESULT_CONTEST_ID "contest_id"
#define PROBLEM_RESULT_USER_ID "user_id"
#define PROBLEM_RESULT_PROBLEM_ID "problem_id"
#define PROBLEM_RESULT_POINTS "points"
#define PROBLEM_RESULT_SUCESS "success"
#define PROBLEM_RESULT_FAILED_TEST_CASE_ID "failed_test_case_id"
#define PROBLEM_RESULT_CREATED_AT "created_at"
#define PROBLEM_RESULT_UPDATED_AT "updated_at"
#define PROBLEM_RESULT_TRIAL_NUMBER "trial_number"

cJSON *create_problem_result_char(int user_id, int contest_id, int problem_id,
                                  int points, int success, void *failed_test_case_id) {
    struct Database *db = new(Database);

    char select_sql[1024];

    sprintf(select_sql, "SELECT COUNT(id)\n"
                    "FROM problem_result\n"
                    "WHERE contest_id=%d \n"
                    "AND user_id=%d \n"
                    "AND problem_id=%d",
            contest_id, user_id, problem_id);


    cJSON *msg = select_query(db, select_sql);

    if ((cJSON_GetObjectItem(msg, "status"))->valueint != DATABASE_TUPLES_OK)
        return msg;

    int trial_number = strtol((cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(msg, "data"), 0),
                                                   "count"))->valuestring, NULL, 10);
    trial_number++;
    cJSON_Delete(msg);
    char param[1];
    sprintf(param, "%d", success);
    char *param_values[2];
    if (failed_test_case_id != 0)
        sprintf(param_values[1], "%d", failed_test_case_id);
    else param_values[1] = failed_test_case_id;
    param_values[0] = param;
    char insert_sql[1024];
    sprintf(insert_sql, "INSERT INTO problem_result \n"
                    "VALUES (DEFAULT, %d, %d, %d, %d, $1, $2, DEFAULT, DEFAULT, %d) \n"
                    "RETURNING id",
            user_id, contest_id, problem_id, points, trial_number);

    msg = insert_query_params(db, insert_sql, 2, param_values);
    delete(db);

    return msg;
}

cJSON *create_problem_result_cJSON(cJSON *data) {
    return create_problem_result_char(
            (cJSON_GetObjectItem(data, PROBLEM_RESULT_USER_ID))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_RESULT_CONTEST_ID))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_RESULT_PROBLEM_ID))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_RESULT_POINTS))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_RESULT_SUCESS))->valueint,
            cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_RESULT_FAILED_TEST_CASE_ID)));
}

cJSON *get_problem_results_in_contest(int user_id, int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM problem_result \n"
                    "where user_id=%d \n"
                    "AND contest_id=%d",
            user_id, contest_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}


cJSON *get_problem_result_trials_in_contest(int user_id, int contest_id, int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM problem_result \n"
                    "where user_id=%d \n"
                    "AND contest_id=%d \n"
                    "AND problem_id=%d",
            user_id, contest_id, problem_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_successful_problem_results_in_contest(int user_id, int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM problem_result \n"
                    "where user_id=%d \n"
                    "AND contest_id=%d \n"
                    "AND success = 1",
            user_id, contest_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_last_successful_problem_result_in_contest(int user_id, int contest_id, int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM problem_result \n"
                    "where user_id=%d \n"
                    "AND contest_id=%d \n"
                    "AND problem_id=%d \n"
                    "AND success=1 \n"
                    "ORDER BY updated_at DESC \n"
                    "LIMIT 1",
            user_id, contest_id, problem_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_all_problem_results_count_in_contest(int user_id, int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT problem_id, COUNT(*) \n"
                    "FROM problem_result \n"
                    "where user_id=%d \n"
                    "AND contest_id=%d \n"
                    "GROUP BY problem_id",
            user_id, contest_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_all_participants_in_contest(int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT users.* \n"
                    "FROM problem_result join users on user_id=users.id \n"
                    "AND contest_id=%d",
            contest_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *problem_result_ctor(void *_self, va_list *arguments) {
    struct ProblemResult *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int prblm_rslt_args = va_arg(*arguments, const int);
    if (prblm_rslt_args == PROBLEM_RESULT_CLONE)
        return self;

    cJSON *create_prblm_rslt_msg = create_problem_result_cJSON(self->data);

    if ((cJSON_GetObjectItem(create_prblm_rslt_msg, "status"))->valueint != DATABASE_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(create_prblm_rslt_msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }

    int problem_result_id = cJSON_parser(
            cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(create_prblm_rslt_msg, "data"), 0), "id"));

    cJSON_AddNumberToObject(self->data, "id", problem_result_id);

    return self;
}

static void *problem_result_clone(const void *_self) {
    const struct ProblemResult *self = _self;
    struct ProblemResult *new_problem_result = new(ProblemResult, self->data, PROBLEM_RESULT_CLONE);
    return new_problem_result;
}

static void problem_result_set(struct ProblemResult *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    int problem_result_id = (cJSON_GetObjectItem(_self->data, PROBLEM_RESULT_ID))->valueint;
    assert(problem_result_id);

    struct Database *db = new(Database);
    char update_sql[1024];
    char *values[] = {value};

    //update user in db;
    sprintf(update_sql, "UPDATE problem_result SET %s=$1 WHERE id=%d", field, problem_result_id);
    cJSON *msg = update_query_params(db, update_sql, 1, values);
    delete(db);
    if ((cJSON_GetObjectItem(msg, "status"))->valueint != DATABASE_NO_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static void *problem_result_get(struct ProblemResult *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int problem_result_differ(const void *_self, const void *_b) {
    const struct ProblemResult *self = _self;
    const struct ProblemResult *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != ProblemResult)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *problem_result_toJson(struct ProblemResult *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *problem_result_dtor(void *_self) {
    struct ProblemResult *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _ProblemResult = {
        sizeof(struct ProblemResult),
        problem_result_ctor,
        problem_result_dtor,
        problem_result_clone,
        problem_result_differ,
        problem_result_set,
        problem_result_get,
        problem_result_toJson
};

const void *ProblemResult = &_ProblemResult;