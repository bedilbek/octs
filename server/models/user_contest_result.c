//
// Created by bedilbek on 12/10/17.
//

#include "user_contest_result.h"

#define USER_CONTEST_RESULT_CLONE 2

#define USER_CONTEST_RESULT_USER_ID "user_id"
#define USER_CONTEST_RESULT_CONTEST_ID "contest_id"
#define USER_CONTEST_RESULT_TOTAL_POINTS "total_points"
#define USER_CONTEST_RESULT_CREATED_AT "created_at"
#define USER_CONTEST_RESULT_UPDATED_AT "updated_at"

cJSON *create_user_contest_result_char(int user_id, int contest_id, int total_points) {
    struct Database *db = new(Database);

    char insert_sql[1024];
    sprintf(insert_sql, "INSERT INTO user_contest_result \n"
                    "VALUES (%d, %d, %d, DEFAULT, DEFAULT)",
            user_id, contest_id, total_points);

    cJSON *msg = insert_query(db, insert_sql);
    delete(db);

    return msg;
}

cJSON *create_user_contest_result_cJSON(cJSON *data) {
    return create_user_contest_result_char(
            (cJSON_GetObjectItem(data, USER_CONTEST_RESULT_USER_ID))->valueint,
            (cJSON_GetObjectItem(data, USER_CONTEST_RESULT_CONTEST_ID))->valueint,
            (cJSON_GetObjectItem(data, USER_CONTEST_RESULT_TOTAL_POINTS))->valueint);
}

cJSON *get_participants_from_contest(int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT users.* \n"
                    "FROM users join user_contest_result ON id=user_id \n"
                    "WHERE contest_id=%d",
            contest_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_contests_of_user(int user_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT contest.* \n"
                    "FROM contest join user_contest_result ON id=contest_id \n"
                    "WHERE user_id=%d",
            user_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_user_contest_result(int user_id, int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM user_contest_result \n"
                    "WHERE user_id=%d \n"
                    "AND contest_id=%d",
            user_id, contest_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *user_contest_result_ctor(void *_self, va_list *arguments) {
    struct UserContestResult *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int tst_cs_args = va_arg(*arguments, const int);
    if (tst_cs_args == USER_CONTEST_RESULT_CLONE)
        return self;

    cJSON *msg = create_user_contest_result_cJSON(self->data);

    if ((cJSON_GetObjectItem(msg, "status"))->valueint != 201) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }

    return self;
}

static void *user_contest_result_clone(const void *_self) {
    const struct UserContestResult *self = _self;
    struct UserContestResult *new_user_contest_result = new(UserContestResult, self->data, USER_CONTEST_RESULT_CLONE);
    return new_user_contest_result;
}

static void user_contest_result_set(struct UserContestResult *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    int contest_id = (cJSON_GetObjectItem(_self->data, USER_CONTEST_RESULT_CONTEST_ID))->valueint;
    int user_id = (cJSON_GetObjectItem(_self->data, USER_CONTEST_RESULT_USER_ID))->valueint;
    assert(contest_id);

    struct Database *db = new(Database);
    char update_sql[1024];
    char *values[] = {value};

    //update user in db;
    sprintf(update_sql, "UPDATE user_contest_result SET %s=$1 \n"
            "WHERE user_id=%d \n"
            "AND contest_id=%d", field, user_id, contest_id);

    cJSON *msg = update_query_params(db, update_sql, 1, values);

    delete(db);

    if ((cJSON_GetObjectItem(msg, "status"))->valueint != 201) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static void *user_contest_result_get(struct UserContestResult *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int user_contest_result_differ(const void *_self, const void *_b) {
    const struct UserContestResult *self = _self;
    const struct UserContestResult *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != UserContestResult)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *user_contest_result_toJson(struct UserContestResult *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *user_contest_result_dtor(void *_self) {
    struct UserContestResult *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _UserContestResult = {
        sizeof(struct UserContestResult),
        user_contest_result_ctor,
        user_contest_result_dtor,
        user_contest_result_clone,
        user_contest_result_differ,
        user_contest_result_set,
        user_contest_result_get,
        user_contest_result_toJson
};

const void *UserContestResult = &_UserContestResult;