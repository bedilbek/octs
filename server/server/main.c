//////
////// Created by Tolqinbek Isoqov on 12/3/17.
//////
//
//#include "lib.h"
//#include <pthread.h>
//#include "server.h"
////
////int main() {
////    setbuf(stdout, NULL);
//    pthread_t server_pid, file_server_pid;
//    struct Server *server = new(Server, SERVER_LISTEN_PORT);
////    struct Server *file_server = new(Server, FILE_SERVER_LISTEN_PORT);
////    pthread_create(&file_server_pid, NULL, file_server_listen, file_server);
//    pthread_create(&server_pid, NULL, server_listen, server);
////    server_listen(server);
//    pthread_join(server_pid, NULL);
////    pthread_join(file_server_pid, NULL);
////}