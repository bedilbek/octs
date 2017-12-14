//
// Created by bedilbek on 11/29/17.
//

#ifndef POSTGRES_TEST_DATABASE_H
#define POSTGRES_TEST_DATABASE_H

#include "libpq-fe.h"
#include "DB_CONFIG.h"
#include "helpers.h"

extern const void *Database;

struct Database {
    const void *class;
    char connInfo[250];
    char *sql;
    PGconn *pgConn;
    PGresult *pgResult;
};

cJSON *insert_query(struct Database *db, char *cmd);

cJSON *insert_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues);

cJSON *select_query(struct Database *db, char *cmd);

cJSON *select_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues);

cJSON *update_query(struct Database *db, char *cmd);

cJSON *update_query_params(struct Database *db, char *cmd, int num_of_params, const char *const *paramValues);


#endif //POSTGRES_TEST_DATABASE_H
