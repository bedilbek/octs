//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#ifndef OS_PROJECT_SERVER_H
#define OS_PROJECT_SERVER_H

#include "lib.h"
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define SERVER_LISTEN_PORT 8000
#define FILE_SERVER_LISTEN_PORT 8001

#define MAX_NUM_CLIENT 20
#define MAX_LENGTH_OF_MESSAGE 1024

#define OK_RESPONSE "200"
#define BAD_REQUEST "400"
#define SERVER_ERROR "500"

extern const void *Server;

struct Server {
    const void *class;
    int opt;
    int addrlen;
    struct sockaddr_in address;
    int server_file_descriptor;
};

struct Request {
    int socket;
    int method;
    cJSON *data;
    char *token;
};

void server_listen(struct Server *self);

void file_server_listen(struct Server *self);

static void *Server_ctor(void *_self, va_list *arguments);


#endif //OS_PROJECT_SERVER_H
