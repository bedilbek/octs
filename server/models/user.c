//
// Created by bedilbek on 12/5/17.
//

#include "user.h"

#define USER_CLONE 2

#define USER_ID "id"
#define USER_FIRST_NAME "fname"
#define USER_LAST_NAME "lname"
#define USER_USERNAME "username"
#define USER_PASSWORD "password"
#define USER_EMAIL "email"

static void *user_ctor(void *_self, va_list *arguments) {
    struct User *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int user_args = va_arg(*arguments, const int);
    if (user_args == USER_CLONE)
        return self;

    cJSON *create_usr_msg = create_user_cJSON(self->data);

    if ((cJSON_GetObjectItem(create_usr_msg, "status"))->valueint != 200) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(create_usr_msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }
    long user_id = strtol((cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(create_usr_msg, "data"), 0),
                                               "id"))->valuestring, NULL, 10);

    cJSON_AddNumberToObject(self->data, "id", user_id);

    return self;
}

cJSON *create_user_cJSON(cJSON *data) {
    struct Database *db = new(Database);
    char insert_sql[1024];

    sprintf(insert_sql, "INSERT INTO users VALUES (DEFAULT, \'%s\', \'%s\', \'%s\', \'%s\', \'%s\') RETURNING id",
            (cJSON_GetObjectItem(data, USER_FIRST_NAME))->valuestring,
            (cJSON_GetObjectItem(data, USER_LAST_NAME))->valuestring,
            (cJSON_GetObjectItem(data, USER_USERNAME))->valuestring,
            (cJSON_GetObjectItem(data, USER_PASSWORD))->valuestring,
            (cJSON_GetObjectItem(data, USER_EMAIL))->valuestring);
    cJSON *msg = insert_query(db, insert_sql);
    delete(db);
    return msg;
}

cJSON *create_user_char(char *fname, char *lname, char *username, char *password, char *email) {
    struct Database *db = new(Database);
    char insert_sql[1024];

    sprintf(insert_sql, "INSERT INTO users VALUES (DEFAULT, \'%s\', \'%s\', \'%s\', \'%s\', \'%s\') RETURNING id",
            fname, lname, username, password, email);
    cJSON *msg = insert_query(db, insert_sql);
    delete(db);
    return msg;
}

cJSON *get_user_by_id(int user_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT * FROM users where id=%d", user_id);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_user_by_username(char *username) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT * FROM users where username=\'%s\'", username);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *exist_user(char *username, char *password) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql, "SELECT * FROM users where username=\'%s\' AND password=\'%s\'", username, password);
    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_all_users() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT * FROM users");
    delete(db);
    return msg;
}

cJSON *get_all_users_count() {
    struct Database *db = new(Database);
    cJSON *msg = select_query(db, "SELECT COUNT(*) FROM users");
    delete(db);
    return msg;
}

static void *user_clone(const void *_self) {
    const struct User *self = _self;
    struct User *new_user = new(User, self->data, USER_CLONE);
    return new_user;
}

static void user_set(struct User *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    char *username = (cJSON_GetObjectItem(_self->data, USER_USERNAME))->valuestring;
    assert(username);

    struct Database *db = new(Database);
    char update_sql[1024];

    //update user in db;
    sprintf(update_sql, "UPDATE users SET %s=\'%s\' WHERE username=\'%s\'", field, value, username);
    cJSON *msg = update_query(db, update_sql);
    delete(db);
    if ((cJSON_GetObjectItem(msg, "status"))->valueint != 201) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static char *user_get(struct User *_self, char *field, void *value) {
    assert(_self && _self->data);
    return (cJSON_GetObjectItem(_self->data, field))->valuestring;
}

static int user_differ(const void *_self, const void *_b) {
    const struct User *self = _self;
    const struct User *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != User)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *user_toJson(struct User *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *user_dtor(void *_self) {
    struct User *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _User = {
        sizeof(struct User),
        user_ctor,
        user_dtor,
        user_clone,
        user_differ,
        user_set,
        user_get,
        user_toJson
};

const void *User = &_User;
