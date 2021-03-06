////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "server.h"
#include "migrations.h"
#include "lib.h"
#include "model.h"
int main() {
    struct Database *db = new(Database);
    run_migrations(db);

    pthread_t server_pid, file_server_pid;
    //run_migrations()
//    printf(cJSON_Print(create_file_char(1, "/hello/ok/")));

    struct Server *server = new(Server, SERVER_LISTEN_PORT);
    struct Server *file_server = new(Server, FILE_SERVER_LISTEN_PORT);
//    pthread_create(&file_server_pid, NULL, file_server_listen, file_server);
    pthread_create(&server_pid, NULL, server_listen, server);
    pthread_join(server_pid, NULL);
//    pthread_join(file_server_pid, NULL);
//    char *token;
//    token = generate_token();
//    printf(token);
}