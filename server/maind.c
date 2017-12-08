#include <stdio.h>
#include "lib.h"
#include "model.h"

int main() {

    //struct String *a = new(String, "text A");
    //printf("%s", toJson(a));
    //struct String *b = clone(a);

    //struct Dict *keyPair = new(Dict, "info", "man");
    //set(keyPair->data, "info", "as");
    //set(keyPair, "info", "as");
    //printf("hello %s", toJson(keyPair));

//    void* b = new(String, "text B");
//
//    if (!differ(a, aa))
//        printf("yeees\n");
//    printf("%s\n", a->text);
//    printf("%s => %s\n", keyPair->key, keyPair->value);
//    struct Database *db = new(Database);
//    cJSON *dbData = select_query(db, "SELECT * FROM users");
//    printf(cJSON_Print(dbData));
//    delete(db);
//    //delete(a),
//    //delete(b), delete(keyPair);
//      cJSON *usrJSON = cJSON_Parse("{\"fname\":\"tom\",\"lname\":\"isaak\",\"username\":\"ttom\",\"password\":\"tom\",\"email\":\"ttom@gmail.com\"}");
//    printf(toJson(usr));
//    set(usr, "fname", "bediko");
//    printf(get(usr, "fname"));
//    printf(get(usr, "username"));
//    delete(usr);
    printf(cJSON_Print(cJSON_GetArrayItem(cJSON_GetObjectItem(get_all_users(), "data"), 0)));

    return 0;


}