//
// Created by bedilbek on 11/29/17.
//

#ifndef POSTGRES_TEST_DATABASE_H
#define POSTGRES_TEST_DATABASE_H

#include "postgresql/libpq-fe.h"
#include "DB_CONFIG.h"
#include "helpers.h"

extern const void *Database;

struct Database {
    const void *class;
    char *connInfo;
    char *sql;
    PGconn *pgConn;
    PGresult *pgResult;
};
/**
int pgConnect(char *connInfo, PGconn **pgConn)
{
    *pgConn = PQconnectdb(connInfo);
    if (PQstatus(*pgConn) != CONNECTION_OK) {
        fprintf(stderr,
                "ERROR: Connection to database failed: %s",
                PQerrorMessage(*pgConn));
        return 0;
    }

    return 1;
}

int pgExecute(char *sqlCommand, PGconn **pgConn, PGresult **pgResult)
{
    *pgResult = PQexec(*pgConn, sqlCommand);
    if (PQresultStatus(*pgResult) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Select query failed: %s", PQerrorMessage(*pgConn));
        PQclear(*pgResult);
        return 0;
    }
    return 1;
}
**/
/*
void displayPGResult(PGresult *pgResult)
{
    int i,j;

    /* first, print out the attribute names */
/*  int nFields = PQnfields(pgResult);

  for (i = 0; i < nFields; i++)
      printf("%-15s", PQfname(pgResult, i));
  printf("\n\n");

  /* next, print out the rows */
/*   for (i = 0; i < PQntuples(pgResult); i++)
   {
       for (j = 0; j < nFields; j++)
           printf("%-15s", PQgetvalue(pgResult, i, j));
       printf("\n");
   }

   PQclear(pgResult);
}
*/

/*
void getResult() {
    sprintf(connInfo,
            "user=%s password=%s dbname=%s hostaddr=%s port=%d",
            PG_USER, PG_PASS, PG_DB, PG_HOST, PG_PORT);

    if (!pgConnect(connInfo, &pgConn)) {
        goto end;
    }

    sprintf(sqlCommand,
            "SELECT * FROM \"euser\"");

    if (!pgExecute(sqlCommand, &pgConn, &pgResult)) {
        goto end;
    }

    displayPGResult(pgResult);

    end:
    PQfinish(pgConn);
}
*/

#endif //POSTGRES_TEST_DATABASE_H
