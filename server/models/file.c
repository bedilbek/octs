//
// Created by bedilbek on 12/14/17.
//

#include "file.h"

#define FILE_CLONE 2

#define FILE_ID "id"
#define FILE_USER_ID "user_id"
#define FILE_PATH "path"
#define FILE_EXTENSION "extension"

cJSON *create_file_char(int user_id, char *path, char *ext) {
    struct Database *db = new(Database);

    char insert_sql[1024];

    sprintf(insert_sql, "INSERT INTO file \n"
                    "VALUES (DEFAULT, %d, \'%s\', \'%s\') \n"
                    "RETURNING *",
            user_id, path, ext);

    cJSON *msg = insert_query(db, insert_sql);
    delete(db);

    return msg;
}

cJSON *create_file_cJSON(cJSON *data) {
    return create_file_char(
            (cJSON_GetObjectItem(data, FILE_USER_ID))->valueint,
            (cJSON_GetObjectItem(data, FILE_PATH))->valuestring,
            (cJSON_GetObjectItem(data, FILE_EXTENSION))->valuestring);
}

cJSON *get_file_by_path(char *file_path) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM file \n"
                    "where path=%s",
            file_path);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_files_of_user(int user_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM file \n"
                    "where user_id=%d",
            user_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}


cJSON *get_file_by_id(int file_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM file \n"
                    "where id=%d",
            file_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *file_ctor(void *_self, va_list *arguments) {
    struct File *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (!data)
        self->data = cJSON_CreateObject();
    return self;

    assert(data);
    const int clone = va_arg(*arguments, const int);
    if (clone == FILE_CLONE)
        return self;

    cJSON *msg = create_file_cJSON(self->data);

    if ((cJSON_GetObjectItem(msg, "status"))->valueint != DATABASE_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }

    cJSON *file = cJSON_parser(
            cJSON_GetArrayItem(cJSON_GetObjectItem(msg, "data"), 0));

    self->data = file;

    return self;
}

static void *file_clone(const void *_self) {
    const struct File *self = _self;
    struct File *new_file = new(File, self->data, FILE_CLONE);
    return new_file;
}

static void file_set(struct File *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    int file_id = (cJSON_GetObjectItem(_self->data, FILE_ID))->valueint;
    assert(file_id);

    struct Database *db = new(Database);
    char update_sql[1024];
    char *values[] = {value};

    //update user in db;
    sprintf(update_sql, "UPDATE file SET %s=$1 WHERE id=%d", field, file_id);
    cJSON *msg = update_query_params(db, update_sql, 1, values);
    delete(db);
    if ((cJSON_GetObjectItem(msg, "status"))->valueint != DATABASE_NO_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static void *file_get(struct File *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int file_differ(const void *_self, const void *_b) {
    const struct File *self = _self;
    const struct File *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != File)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *file_toJson(struct File *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *file_dtor(void *_self) {
    struct File *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _File = {
        sizeof(struct File),
        file_ctor,
        file_dtor,
        file_clone,
        file_differ,
        file_set,
        file_get,
        file_toJson
};

const void *File = &_File;


char *get_file_path(int file_id)
{
    cJSON *response = get_file_by_id(file_id);
    if (((int) cJSON_parser(cJSON_GetObjectItem(response, "status"))) != DATABASE_TUPLES_OK)
    {
        return  NULL;
    }

    return (char *) cJSON_parser( cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(response, "data"), 0), "path"));
}