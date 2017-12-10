//
// Created by bedilbek on 12/9/17.
//

#include "contest.h"

#define CONTEST_CLONE 2

#define CONTEST_ID "id"
#define CONTEST_AUTHOR_ID "author_id"
#define CONTEST_STARTS_AT "starts_at"
#define CONTEST_ENDS_AT "ends_at"
#define CONTEST_CREATED_AT "created_at"
#define CONTEST_UPDATED_AT "updated_at"
#define CONTEST_DESCRIPTION "description"

cJSON *create_contest_char(int author_id, char *starts_at, char *ends_at,
                           char *description) {
    struct Database *db = new(Database);
    char insert_sql[1024];
    char *paramvalues[] = {starts_at, ends_at};
    sprintf(insert_sql, "INSERT INTO contest VALUES (DEFAULT, %d, $1, $2, DEFAULT, DEFAULT, \'%s\') RETURNING id",
            author_id, description);

    cJSON *msg = insert_query_params(db, insert_sql, 2, paramvalues);
    delete(db);
    return msg;
}

cJSON *create_contest_cJSON(cJSON *data) {
    return create_contest_char(
            (cJSON_GetObjectItem(data, CONTEST_AUTHOR_ID))->valueint,
            (cJSON_GetObjectItem(data, CONTEST_STARTS_AT))->valuestring,
            (cJSON_GetObjectItem(data, CONTEST_ENDS_AT))->valuestring,
            (cJSON_GetObjectItem(data, CONTEST_DESCRIPTION))->valuestring);
}

cJSON *get_contest_by_id(int contest_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT * FROM contest where id=%d", contest_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_all_contests() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT * FROM contest");
    delete(db);
    return msg;
}

cJSON *get_all_contests_count() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT COUNT(*) FROM contest");
    delete(db);
    return msg;
}

cJSON *get_contest_by_authorId(int author_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT contest.* FROM users join contest on users.id=contest.author_id where author_id=%d",
            author_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *contest_ctor(void *_self, va_list *arguments) {
    struct Contest *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int cntst_args = va_arg(*arguments, const int);
    if (cntst_args == CONTEST_CLONE)
        return self;

    cJSON *create_cntst_msg = create_contest_cJSON(self->data);

    if ((cJSON_GetObjectItem(create_cntst_msg, "status"))->valueint != 200) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(create_cntst_msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }

    int contest_id = cJSON_parser(
            cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(create_cntst_msg, "data"), 0), "id"));

    cJSON_AddNumberToObject(self->data, "id", contest_id);

    return self;
}

static void *contest_clone(const void *_self) {
    const struct Contest *self = _self;
    struct Contest *new_contest = new(Contest, self->data, CONTEST_CLONE);
    return new_contest;
}

static void contest_set(struct Contest *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    int contest_id = (cJSON_GetObjectItem(_self->data, CONTEST_ID))->valueint;
    assert(contest_id);

    struct Database *db = new(Database);
    char update_sql[1024];
    char *values[] = {value};

    //update user in db;
    sprintf(update_sql, "UPDATE contest SET %s=$1 WHERE id=%d", field, contest_id);
    cJSON *msg = update_query_params(db, update_sql, 1, values);
    delete(db);
    if ((cJSON_GetObjectItem(msg, "status"))->valueint != 201) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static void *contest_get(struct Contest *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int contest_differ(const void *_self, const void *_b) {
    const struct Contest *self = _self;
    const struct Contest *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != Contest)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *contest_toJson(struct Contest *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *contest_dtor(void *_self) {
    struct Contest *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _Contest = {
        sizeof(struct Contest),
        contest_ctor,
        contest_dtor,
        contest_clone,
        contest_differ,
        contest_set,
        contest_get,
        contest_toJson
};

const void *Contest = &_Contest;