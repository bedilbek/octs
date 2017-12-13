//
// Created by bedilbek on 12/9/17.
//

#include "contest_problem.h"

#define CONTEST_PROBLEM_CLONE 2

#define CONTEST_PROBLEM_ID "id"
#define CONTEST_PROBLEM_CONTEST_ID "contest_id"
#define CONTEST_PROBLEM_PROBLEM_ID "problem_id"
#define CONTEST_PROBLEM_CREATED_AT "created_at"
#define CONTEST_PROBLEM_UPDATED_AT "updated_at"

cJSON *create_contest_problem_char(int contest_id, int problem_id) {
    struct Database *db = new(Database);
    char insert_sql[1024];
    sprintf(insert_sql, "INSERT INTO contest_problem VALUES (%d, %d, DEFAULT, DEFAULT)",
            contest_id, problem_id);

    cJSON *msg = insert_query(db, insert_sql);
    delete(db);
    return msg;
}

cJSON *create_contest_problem_cJSON(cJSON *data) {
    return create_contest_problem_char(
            (cJSON_GetObjectItem(data, CONTEST_PROBLEM_CONTEST_ID))->valueint,
            (cJSON_GetObjectItem(data, CONTEST_PROBLEM_PROBLEM_ID))->valueint);
}

cJSON *get_contests_by_problem_id(int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT contest.* FROM contest join contest_problem on id=contest_id where problem_id=%d",
            problem_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_problems_by_contest_id(int contest_id, char *order) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT problem.* FROM problem join contest_problem on id=problem_id where contest_id=%d ORDER "
            "BY id %s", contest_id, order);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_all_problems_count_by_contests() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT contest_id as id, COUNT(problem_id) FROM contest_problem GROUP BY id");
    delete(db);
    return msg;
}

cJSON *get_problems_count_by_contest_id(int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT contest_id as id, COUNT(problem_id) FROM contest_problem WHERE contest_id=%d GROUP BY id",
            contest_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *contest_problem_ctor(void *_self, va_list *arguments) {
    struct ContestProblem *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int cntst_prblm_args = va_arg(*arguments, const int);
    if (cntst_prblm_args == CONTEST_PROBLEM_CLONE)
        return self;

    cJSON *create_cntst_prblm_msg = create_contest_problem_cJSON(self->data);

    if ((cJSON_GetObjectItem(create_cntst_prblm_msg, "status"))->valueint != 201) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(create_cntst_prblm_msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }

    return self;
}

static void *contest_problem_clone(const void *_self) {
    const struct ContestProblem *self = _self;
    struct ContestProblem *new_contest_problem = new(ContestProblem, self->data, CONTEST_PROBLEM_CLONE);
    return new_contest_problem;
}

static void contest_problem_set(struct ContestProblem *_self, char *field, void *value) {
    return;
}

static void *contest_problem_get(struct ContestProblem *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int contest_problem_differ(const void *_self, const void *_b) {
    const struct ContestProblem *self = _self;
    const struct ContestProblem *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != ContestProblem)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *contest_problem_toJson(struct ContestProblem *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *contest_problem_dtor(void *_self) {
    struct ContestProblem *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _ContestProblem = {
        sizeof(struct ContestProblem),
        contest_problem_ctor,
        contest_problem_dtor,
        contest_problem_clone,
        contest_problem_differ,
        contest_problem_set,
        contest_problem_get,
        contest_problem_toJson
};

const void *ContestProblem = &_ContestProblem;