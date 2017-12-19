//
// Created by bedilbek on 12/7/17.
//

#include "problem.h"

#define PROBLEM_CLONE 2

#define PROBLEM_ID "id"
#define PROBLEM_CATEGORY_ID "category_id"
#define PROBLEM_DESCRIPTION "description"
#define PROBLEM_INPUT_FILE_ID "input_file_id"
#define PROBLEM_OUTPUT_FILE_ID "output_file_id"
#define PROBLEM_TIME_LIMIT "time_limit"
#define PROBLEM_MEMORY_LIMIT "memory_limit"
#define PROBLEM_MAX_POINTS "max_points"
#define PROBLEM_CREATED_AT "created_at"
#define PROBLEM_UPDATED_AT "updated_at"
#define PROBLEM_TITLE "title"

cJSON *create_problem_char(int category_id, char *description, int input_file_id,
                           int output_file_id, int time_limit, int memory_limit,
                           int max_points, char *title) {
    struct Database *db = new(Database);
    char insert_sql[1024];

    sprintf(insert_sql,
            "INSERT INTO problem VALUES (DEFAULT, %d, \'%s\', %d, %d, %d, %d, %d, DEFAULT, DEFAULT, \'%s\') RETURNING *",
            category_id, description, input_file_id, output_file_id, time_limit, memory_limit, max_points, title);

    cJSON *msg = insert_query(db, insert_sql);
    delete(db);
    return msg;
}

cJSON *create_problem_cJSON(cJSON *data) {
    struct Database *db = new(Database);
    char insert_sql[1024];

    sprintf(insert_sql, "INSERT INTO problem VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', %d, %d, %d) RETURNING id",
            (cJSON_GetObjectItem(data, PROBLEM_CATEGORY_ID))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_DESCRIPTION))->valuestring,
            (cJSON_GetObjectItem(data, PROBLEM_INPUT_FILE_ID))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_OUTPUT_FILE_ID))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_TIME_LIMIT))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_MEMORY_LIMIT))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_MAX_POINTS))->valueint,
            (cJSON_GetObjectItem(data, PROBLEM_TITLE))->valuestring);
    cJSON *msg = insert_query(db, insert_sql);
    delete(db);
    return msg;
}

cJSON *get_problem_by_id(int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT problem.*,\n"
            "  category.name as \"category\"\n"
            "FROM problem\n"
            "  JOIN category ON category_id=category.id\n"
            "WHERE problem.id = %d", problem_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *validate_problem(int user_id, int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT\n"
            "  problem.*,\n"
            "  category.name\n"
            "FROM problem\n"
            "  JOIN category ON category.id = problem.category_id\n"
            "  JOIN contest_problem ON contest_problem.problem_id = problem.id\n"
            "  JOIN user_contest_result ON contest_problem.contest_id=user_contest_result.contest_id\n"
            "WHERE user_contest_result.user_id=%d AND problem.id=%d", user_id, problem_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_all_problems() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT * FROM problem WHERE problem.id not in "
            "(SELECT contest_problem.problem_id FROM contest_problem)");
    delete(db);
    return msg;
}

cJSON *get_all_problems_count() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT COUNT(*) FROM problem");
    delete(db);
    return msg;
}

cJSON *get_problems_by_categoryId(int category_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT * FROM problem where category_id=%d", category_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *problem_ctor(void *_self, va_list *arguments) {
    struct Problem *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int user_args = va_arg(*arguments, const int);
    if (user_args == PROBLEM_CLONE)
        return self;

    cJSON *create_prblm_msg = create_problem_cJSON(self->data);

    if ((cJSON_GetObjectItem(create_prblm_msg, "status"))->valueint != DATABASE_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(create_prblm_msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }
    int problem_id = cJSON_parser(
            cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(create_prblm_msg, "data"), 0), "id"));

    cJSON_AddNumberToObject(self->data, "id", problem_id);

    return self;
}

static void *problem_clone(const void *_self) {
    const struct Problem *self = _self;
    struct Problem *new_problem = new(Problem, self->data, PROBLEM_CLONE);
    return new_problem;
}

static void problem_set(struct Problem *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    int problem_id = cJSON_parser(cJSON_GetObjectItem(_self->data, PROBLEM_ID));
    assert(problem_id);

    struct Database *db = new(Database);
    char update_sql[1024];
    char *values[] = {value};

    //update user in db;
    sprintf(update_sql, "UPDATE problem SET %s=$1 WHERE id=%d", field, problem_id);
    cJSON *msg = update_query_params(db, update_sql, 1, values);
    delete(db);
    if ((cJSON_GetObjectItem(msg, "status"))->valueint != DATABASE_NO_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static void *problem_get(struct Problem *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int problem_differ(const void *_self, const void *_b) {
    const struct Problem *self = _self;
    const struct Problem *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != Problem)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *problem_toJson(struct Problem *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *problem_dtor(void *_self) {
    struct Problem *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _Problem = {
        sizeof(struct Problem),
        problem_ctor,
        problem_dtor,
        problem_clone,
        problem_differ,
        problem_set,
        problem_get,
        problem_toJson
};

const void *Problem = &_Problem;

void *map_problem(cJSON *from) {
    struct Problem *to;
    to = malloc(sizeof(struct Problem));
    int status = (int) cJSON_parser(cJSON_GetObjectItem(from, "status"));

    if (status == DATABASE_TUPLES_OK) {
        cJSON *data;
        data = cJSON_GetArrayItem(cJSON_GetObjectItem(from, "data"), 0);
        to->id = (int) cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_ID));
        to->category_id = (int) cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_CATEGORY_ID));
        to->description = (char *) cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_DESCRIPTION));
        to->max_point = (int) cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_MAX_POINTS));
        to->memory_limit = (int) cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_MEMORY_LIMIT));
        to->time_limit = (int) cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_TIME_LIMIT));
        to->title = (char *) cJSON_parser(cJSON_GetObjectItem(data, PROBLEM_TITLE));
    }

    return to;
}