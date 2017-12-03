////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "server/server.c"

int main() {
    struct Server server = {};
    server = Server_ctor(server);
    server_listen(server);
}

//
// Created by Tolqinbek Isoqov on 11/19/17.
//
//
//#include <unistd.h>
//#include <stdio.h>
//#include <sys/socket.h>
//#include <stdlib.h>
//#include <netinet/in.h>
//
//#define PORT 8080
//
//typedef struct Server server_type;
//
//struct Server {
//    int server_file_descriptor, new_socket, val_read;
//    struct sockaddr_in address;
//    int opt;
//    int addrlen;
//    char buffer[1024];
//
//    void (*create_sock)(server_type *server);
//
//    void (*attach_sock)(server_type *server);
//
//    void (*set_sockaddr)(server_type *server);
//
//    void (*attach_port)(server_type *server);
//
//    void (*listen_port)(server_type *server, int number);
//
//    void (*accept_connection)(server_type *server);
//
//};
//
//void create_sock(server_type *server) {
//    /**
//     * Create socket file descriptor
//     */
//    if ((server->server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//        perror("Creating socket descriptor file is failed");
//        exit(EXIT_FAILURE);
//    }
//}
//
//void attach_sock(server_type *server) {
//    /**
//     * Setting option of socket file
//     */
//    if (setsockopt(server->server_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &server->opt,
//                   sizeof(server->opt))) {
//        perror("Failed setting pt of socket");
//        exit(EXIT_FAILURE);
//    }
//}
//
//void set_sockaddr(server_type *server) {
//    /**
//     * Setting address properties
//     */
//    server->address.sin_family = AF_INET;
//    server->address.sin_addr.s_addr = INADDR_ANY;
//    server->address.sin_port = htons(PORT);
//}
//
//void attach_port(server_type *server) {
//    if (bind(server->server_file_descriptor, (struct sockaddr *) &server->address, sizeof(server->address)) < 0) {
//        perror("Failed binding port");
//        exit(EXIT_FAILURE);
//    }
//}
//
//void listen_port(server_type *server, int number) {
//    if (listen(server->server_file_descriptor, number) < 0) {
//        perror("listen");
//        exit(EXIT_FAILURE);
//    }
//}
//
//void accept_connection(server_type *server) {
//    if ((server->new_socket = accept(server->server_file_descriptor, (struct sockaddr *) &server->address,(socklen_t *) &server->addrlen)) < 0) {
//         perror("accept");
//        exit(EXIT_FAILURE);
//    }
//}
//
//
//server_type new(server_type server) {
//    server.opt = 1;
//    server.addrlen = sizeof(server.address);
//    *server.buffer = NULL;
//    server.create_sock = create_sock;
//    server.attach_sock = attach_sock;
//    server.set_sockaddr = set_sockaddr;
//    server.attach_port = attach_port;
//    server.listen_port = listen_port;
//    server.accept_connection = accept_connection;
//    return server;
//}
//
//void start_server(server_type server) {
//    server.create_sock(&server);
//    server.attach_sock(&server);
//    server.set_sockaddr(&server);
//    server.attach_port(&server);
//    server.listen_port(&server, 10);
//    while (1) {
//        server.accept_connection(&server);
//        server.val_read = read(server.new_socket, server.buffer, 1024);
//        printf("%s\n", server.buffer);
//    }
//
//}
//
//int main() {
//    server_type server = {};
//    server = new(server);
//    start_server(server);
//}