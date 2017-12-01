//
// Created by bedilbek on 11/29/17.
//

#include "DataBase.h"

static void *Database_ctor(void *_self, va_list *arguments) {
    struct Database *self = _self;

    const char *connInfo = va_arg(*arguments, const char *);
    self->connInfo = malloc(strlen(connInfo) + 1);
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
    free(self->connInfo), self->connInfo = 0;
    free(self->pgResult), self->pgResult = 0;
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