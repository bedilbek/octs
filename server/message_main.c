////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "server.h"
#include "db/migration/migrations.h"
#include "lib.h"
#include "model.h"

int main() {
//    struct Database *db = new(Database);
//    run_migrations(db);
    pthread_t server_pid;
    struct Server *server = new(Server, SERVER_LISTEN_PORT);
    pthread_create(&server_pid, NULL, server_listen, server);
    pthread_join(server_pid, NULL);
}