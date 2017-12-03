//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#ifndef OS_PROJECT_SERVER_H
#define OS_PROJECT_SERVER_H

#include <evrpc.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000
#define MAX_NUM_CLIENT 20


struct Server {
    const void *class;
    int opt;
    int addrlen;
    char buffer[1024];
    struct sockaddr_in address;
    int server_file_descriptor, new_socket, val_read;
};

#endif //OS_PROJECT_SERVER_H
