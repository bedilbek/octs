//
// Created by bedilbek on 11/29/17.
//

#include "DataBase.h"

#define INSERTION_QUERY "Insertion"
#define UPDATE_QUERY "Update"
#define SELECTION_QUERY "Selection"

#define TYPE_VARCHAR 1043
#define TYPE_TIMESTAMP 1114
#define TYPE_INTEGER 23
#define TYPE_BOOL 16
#define TYPE_TEXT 25

cJSON *parseResult(PGresult *pgResult);

cJSON *execute_query(struct Database *db, char *cmd);

cJSON *execute_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues);

static void *Database_ctor(void *_self, va_list *arguments) {
    struct Database *self = _self;
    char connInfo[250];
    sprintf(connInfo, "user=%s password=%s dbname=%s hostaddr=%s port=%d",
            PG_USER, PG_PASS, PG_DB, PG_HOST, PG_PORT);
    assert(self->connInfo);
    strcpy(self->connInfo, connInfo);

    PGconn *pgConn = PQconnectdb(connInfo);

    if (PQstatus(pgConn) != CONNECTION_OK) {
        fprintf(stderr,
                "ERROR: Connection to database failed: %s",
                PQerrorMessage(pgConn));
        exit(0);
    }

    assert(pgConn);

    self->pgConn = malloc(sizeof(PGconn *));
    self->pgConn = pgConn;

    assert(self->pgConn);

    return self;
}

static void *Database_dtor(void *_self) {
    struct Database *self = _self;

    free(self->pgConn), self->pgConn = 0;
    free(self->sql), self->sql = 0;

    return self;
}


static void *Database_clone(const void *_self) {
    const struct Database *self = _self;
    return new(Database, self->connInfo);
}


static const struct Class _Database = {
        sizeof(struct Database),
        Database_ctor,
        Database_dtor,
        Database_clone
};

const void *Database = &_Database;

cJSON *insert_query(struct Database *db, char *cmd) {
    cJSON *result = execute_query(db, cmd);
    check_pg_result(db, result, INSERTION_QUERY);
    return result;
}

cJSON *insert_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues) {
    cJSON *result = execute_query_params(db, cmd, num_of_params, paramValues);
    check_pg_result(db, result, INSERTION_QUERY);
    return result;
}

cJSON *select_query(struct Database *db, char *cmd) {
    cJSON *result = execute_query(db, cmd);
    check_pg_result(db, result, SELECTION_QUERY);
    return result;
}

cJSON *select_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues) {
    cJSON *result = execute_query_params(db, cmd, num_of_params, paramValues);
    check_pg_result(db, result, SELECTION_QUERY);
    return result;
}

cJSON *update_query(struct Database *db, char *cmd) {
    cJSON *result = execute_query(db, cmd);
    check_pg_result(db, result, UPDATE_QUERY);
    return result;
}

cJSON *update_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues) {
    cJSON *result = execute_query_params(db, cmd, num_of_params, paramValues);
    check_pg_result(db, result, UPDATE_QUERY);
    return result;
}

void check_pg_result(struct Database *db, cJSON *result, char *query_type) {
    if (!db->pgResult)
        return;

    if (PQresultStatus(db->pgResult) != PGRES_COMMAND_OK) {
        char message[1024];

        cJSON_DeleteItemFromObject(result, "status");
        cJSON_DeleteItemFromObject(result, "message");

        cJSON_AddNumberToObject(result, "status", 506);
        sprintf(message, "Execution of %s query failed: %s", INSERTION_QUERY, PQerrorMessage(db->pgConn));
        cJSON_AddStringToObject(result, "message", message);
    }

    if (PQresultStatus(db->pgResult) == PGRES_TUPLES_OK) {
        cJSON_DeleteItemFromObject(result, "status");
        cJSON_DeleteItemFromObject(result, "message");

        cJSON_AddNumberToObject(result, "status", 200);
        cJSON_AddStringToObject(result, "message", "OK");

        cJSON *data = parseResult(db->pgResult);

        cJSON_AddItemToObject(result, "data", data);

        cJSON_AddNumberToObject(result, "count", PQntuples(db->pgResult));
    }

    if (PQresultStatus(db->pgResult) == PGRES_COMMAND_OK) {
        cJSON_DeleteItemFromObject(result, "status");
        cJSON_DeleteItemFromObject(result, "message");

        cJSON_AddNumberToObject(result, "status", 201);
        cJSON_AddStringToObject(result, "message", "OK");
    }

    PQclear(db->pgResult);
    db->pgResult = NULL;
}

cJSON *execute_query(struct Database *db, char *cmd) {
    cJSON *result = execute_query_params(db, cmd, 0, NULL);
    return result;
}

cJSON *execute_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues) {

    cJSON *result = cJSON_CreateObject();

    cJSON_AddNumberToObject(result, "status", 505);
    cJSON_AddStringToObject(result, "message", "Connection to database failed");
    cJSON_AddItemToObject(result, "data", NULL);

    if (!db->pgConn)
        return result;

    if (db->pgResult)
        PQclear(db->pgResult);

    db->pgResult = PQexecParams(db->pgConn, cmd, num_of_params, NULL, paramValues, NULL, NULL, 0);

    return result;
}

cJSON *parseResult(PGresult *pgResult) {
    if (!pgResult)
        return NULL;

    cJSON *data = cJSON_CreateArray();

    int i, j;
    int nFields = PQnfields(pgResult);
    int nTuples = PQntuples(pgResult);

    for (i = 0; i < nTuples; i++) {
        cJSON *object = cJSON_CreateObject();
        for (j = 0; j < nFields; j++) {
            if (PQgetisnull(pgResult, i, j)) {
                cJSON_AddNullToObject(object, PQfname(pgResult, j));
            } else {
                int length = PQgetlength(pgResult, i, j);
                char *value = PQgetvalue(pgResult, i, j);

                switch (PQftype(pgResult, j)) {
                    case TYPE_BOOL:
                        cJSON_AddBoolToObject(object, PQfname(pgResult, j), (int) strtol(value, NULL, 10));
                        break;
                    case TYPE_INTEGER:
                        cJSON_AddNumberToObject(object, PQfname(pgResult, j), (int) strtol(value, NULL, 10));
                        break;
                    case TYPE_TEXT:
                        cJSON_AddStringToObject(object, PQfname(pgResult, j), value);
                        break;
                    case TYPE_TIMESTAMP:
                        cJSON_AddStringToObject(object, PQfname(pgResult, j), value);
                        break;
                    case TYPE_VARCHAR:
                        cJSON_AddStringToObject(object, PQfname(pgResult, j), value);
                        break;
                    default:
                        cJSON_AddStringToObject(object, PQfname(pgResult, j), value);
                        break;
                }
            }
        }
        cJSON_AddItemToArray(data, object);
    }

    return data;
}