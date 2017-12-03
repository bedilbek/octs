//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#ifndef OS_PROJECT_CLIENT_H
#define OS_PROJECT_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "../cJSON/cJSON.h"
#include "../cJSON/cJSON.c"
#include <sys/socket.h>

#define CLIENT_SEND_PORT 8000
#define CLIENT_LISTEN_PORT 8001
#define SERVER "127.0.0.1"

struct Client {
    struct sockaddr_in address;
    int sock, valread;
    struct sockaddr_in serv_addr;
    char *hello;
    char buffer[1024];
};
#endif //OS_PROJECT_CLIENT_H
