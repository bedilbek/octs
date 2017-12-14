//
// Created by Tolqinbek Isoqov on 12/3/17.
//

#ifndef OS_PROJECT_CLIENT_H
#define OS_PROJECT_CLIENT_H

#include "lib.h"


#define SERVER_LISTEN_PORT 8000
#define FILE_SERVER_LISTEN_PORT 8001
#define SERVER "127.0.0.1"
#define MAX_LENGTH_OF_MESSAGE 1024

extern const void *Client;

struct Client {
    void *class;
    struct sockaddr_in address;
    int sock, valread;
    struct sockaddr_in serv_addr;
};

cJSON *client_listen(struct Client *client);

void *send_message(struct Client *client, char *token, int method, cJSON *params);

void *send_file(struct Client *client, char *absolute_path, char *filename);

static void *client_ctor(void *_self, va_list *arguments);

#endif //OS_PROJECT_CLIENT_H
