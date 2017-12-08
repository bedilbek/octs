//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#ifndef OS_PROJECT_SERVER_H
#define OS_PROJECT_SERVER_H


#include "lib.h"

#define TRUE 1
#define FALSE 0
#define MAX_NUM_CLIENT 20
#define SERVER_SEND_PORT 8001
#define SERVER_LISTEN_PORT 8000
#define MAX_LENGTH_OF_MESSAGE 1024

#define OK_RESPONSE "200"
#define BAD_REQUEST "400"
#define SERVER_ERROR "500"

extern const void *Server;

struct Server {
    const void *class;
    int opt;
    int addrlen;
    char buffer[1024];
    struct sockaddr_in address;
    int server_file_descriptor, new_socket, val_read;
};

static void dispatch(int socket);

cJSON *get_attr(cJSON *data, char *field);

void server_listen(struct Server *self);

#endif //OS_PROJECT_SERVER_H
