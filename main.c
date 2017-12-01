#include <stdio.h>
#include "helpers.h"
#include "DataBase.h"

int main() {

    //struct String* a = new(String, "text A");
    //struct String* b = clone(a);

    struct Dict *keyPair = new(Dict, "info", "man");
    //set(keyPair->data, "info", "as");
    set(keyPair, "info", "as");
    printf(toJson(keyPair));

//    void* b = new(String, "text B");
//
//    if (!differ(a, aa))
//        printf("yeees\n");
//    printf("%s\n", a->text);
//    printf("%s => %s\n", keyPair->key, keyPair->value);
//    char con[250];
//    sprintf(con, "user=%s password=%s dbname=%s hostaddr=%s port=%d",
//            PG_USER, PG_PASS, PG_DB, PG_HOST, PG_PORT);
//    PGconn *pgConn = PQconnectdb(con);
//
//    struct Database* db = new(Database, con);
//    delete(a), delete(aa), delete(b), delete(keyPair);
    return 0;


}