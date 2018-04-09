//
// Created by bedilbek on 12/9/17.
//

#include "category.h"

#define CATEGORY_CLONE 2

#define CATEGORY_ID "id"
#define CATEGORY_NAME "name"
#define CATEGORY_DESCRIPTION "description"
#define CATEGORY_CREATED_AT "created_at"
#define CATEGORY_UPDATED_AT "updated_at"

cJSON *create_category_char(char *name, char *description) {
    struct Database *db = new(Database);
    char insert_sql[1024];

    sprintf(insert_sql, "INSERT INTO category VALUES (DEFAULT, \'%s\', \'%s\', DEFAULT, DEFAULT) RETURNING id",
            name, description);

    cJSON *msg = insert_query(db, insert_sql);
    delete(db);
    return msg;
}

cJSON *create_category_cJSON(cJSON *data) {
    struct Database *db = new(Database);
    char insert_sql[1024];

    sprintf(insert_sql, "INSERT INTO category VALUES (DEFAULT, \'%s\', \'%s\', DEFAULT, DEFAULT) RETURNING id",
            (cJSON_GetObjectItem(data, CATEGORY_NAME))->valuestring,
            (cJSON_GetObjectItem(data, CATEGORY_DESCRIPTION))->valuestring);

    cJSON *msg = insert_query(db, insert_sql);
    delete(db);
    return msg;
}

cJSON *get_category_by_id(int category_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT * FROM category where id=%d", category_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_all_categories() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT * FROM category");
    delete(db);
    return msg;
}

cJSON *get_all_categories_count() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT COUNT(*) FROM category");
    delete(db);
    return msg;
}

cJSON *get_category_by_problemId(int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT category.* FROM problem join category on problem.category_id=category.id where problem.id=%d",
            problem_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *category_ctor(void *_self, va_list *arguments) {
    struct Category *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int ctgr_args = va_arg(*arguments, const int);
    if (ctgr_args == CATEGORY_CLONE)
        return self;

    cJSON *create_ctgr_msg = create_category_cJSON(self->data);

    if ((cJSON_GetObjectItem(create_ctgr_msg, "status"))->valueint != DATABASE_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(create_ctgr_msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }

    int category_id = cJSON_parser(
            cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(create_ctgr_msg, "data"), 0), "id"));

    cJSON_AddNumberToObject(self->data, "id", category_id);

    return self;
}

static void *category_clone(const void *_self) {
    const struct Category *self = _self;
    struct Category *new_category = new(Category, self->data, CATEGORY_CLONE);
    return new_category;
}

static void category_set(struct Category *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    int category_id = (cJSON_GetObjectItem(_self->data, CATEGORY_ID))->valueint;
    assert(category_id);

    struct Database *db = new(Database);
    char update_sql[1024];
    char *values[] = {value};

    //update user in db;
    sprintf(update_sql, "UPDATE category SET %s=$1 WHERE id=%d", field, category_id);
    cJSON *msg = update_query_params(db, update_sql, 1, values);
    delete(db);
    if ((cJSON_GetObjectItem(msg, "status"))->valueint != DATABASE_NO_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static void *category_get(struct Category *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int category_differ(const void *_self, const void *_b) {
    const struct Category *self = _self;
    const struct Category *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != Category)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *category_toJson(struct Category *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *category_dtor(void *_self) {
    struct Category *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _Category = {
        sizeof(struct Category),
        category_ctor,
        category_dtor,
        category_clone,
        category_differ,
        category_set,
        category_get,
        category_toJson
};

const void *Category = &_Category;