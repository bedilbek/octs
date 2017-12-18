////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "server.h"
#include "migrations.h"
#include "lib.h"
#include "model.h"

int main() {
//    struct Database *db = new(Database);
//    run_migrations(db);

    pthread_t file_server_pid;
    struct Server *file_server = new(Server, FILE_SERVER_LISTEN_PORT);
    pthread_create(&file_server_pid, NULL, file_server_listen, file_server);
    pthread_join(file_server_pid, NULL);
//    char *token;
//    token = generate_token();
//    printf(token);
}