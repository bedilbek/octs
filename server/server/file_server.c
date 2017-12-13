//
// Created by Tolqinbek Isoqov on 12/12/17.
//


#include "server.h"
#include <pthread.h>
#include "controllers.h"

cJSON *get_attr(cJSON *data, char *field) {
    return cJSON_GetObjectItem(data, field);
}

void return_response(int socket, cJSON *response) {
    char *response_message = cJSON_Print(response);
    send(socket, response_message, strlen(response_message), 0);
}

const char *get_full_path(char *file_name) {
    //TODO: make file management
    char *base_path = "/Users/tom1/Documents/Subject files/OS/Project/octs/media/files/";
    char *absolute_path = (char *) malloc(1 + strlen(base_path) + strlen(file_name));
    strcpy(absolute_path, base_path);
    strcat(absolute_path, file_name);
    return absolute_path;
}

void receive_file(int peer_socket) {
    ////init variables
    int len;
    int file_size = 0;
    FILE *received_file;
    char buffer[MAX_LENGTH_OF_MESSAGE];

    read(peer_socket, buffer, MAX_LENGTH_OF_MESSAGE); ////receive metadata about coming file

    ////separate request into datum
    cJSON *message = cJSON_Parse(buffer);
    cJSON *token = get_attr(message, "token");
    cJSON *length = get_attr(message, "length");
    cJSON *file_name = get_attr(message, "file_name");
    for (int i = 0; i < sizeof(buffer); ++i) {
        buffer[i] = '\0';
    }
    file_size = length->valueint;
    const char *absolute_file_path = get_full_path(file_name->valuestring);
    received_file = fopen(absolute_file_path, "w");
    if (received_file == NULL) {
        return;
    }

    while (TRUE) {
        len = (int) read(peer_socket, buffer, MAX_LENGTH_OF_MESSAGE);
        file_size -= len;
        if (file_size < 0 || len == 0) {
            fprintf(received_file, "%s", buffer);
            break;
        }
        fprintf(received_file, "%s", buffer);
    }
    fclose(received_file);

    cJSON_AddStringToObject(message, "file", absolute_file_path);
    cJSON *response = methods[1](message);
    return_response(peer_socket, response);
}

void file_server_listen(struct Server *self) {
    while (TRUE) {
        int peer_socket;
        pthread_t pid;
        if ((peer_socket = accept(self->server_file_descriptor, (struct sockaddr *) &self->address,
                                  (socklen_t *) &self->addrlen)) < 0) {
            perror("accept");
        }
        pthread_create(&pid, NULL, (void *) receive_file, (void *) peer_socket);
    }
}
