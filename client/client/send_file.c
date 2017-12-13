//
// Created by Tolqinbek Isoqov on 12/12/17.
//

#include <sys/stat.h>
#include <errno.h>
#include "client.h"

void *send_file(struct Client *client, char *absolute_path, char *filename) {
    ////Init variables
    ssize_t len;
    struct stat file_stat;
    char request[1024];
    FILE *file;
    int file_length;

    file = fopen(absolute_path, "r");
    stat(absolute_path, &file_stat);
    if (file < 0) {
        cJSON *response = cJSON_CreateObject();
        cJSON_AddStringToObject(response, "non_field_error", strerror(errno));
        return response;
    }
    file_length = file_stat.st_size;

    sprintf(request, "{\"token\":\"%s\", \"length\":%d, \"file_name\": \"%s\"}", "TOKEN 12", file_length,
            filename);
    len = send(client->sock, request, sizeof(request), 0);
    for (int i = 0; i < sizeof(request); ++i) {
        request[i] = '\0';
    }
    if (len < 0) {
        cJSON *response = cJSON_CreateObject();
        cJSON_AddStringToObject(response, "non_field_error", "File can not be sent");
        return response;
    }
    char character;
    int length = -1;
    while (1) {
        character = fgetc(file);
        length++;
        request[length] = character;
        if (length == MAX_LENGTH_OF_MESSAGE) {
            send(client->sock, request, sizeof(request), 0);
            for (int i = 0; i < sizeof(request); ++i) {
                request[i] = '\0';
            }
            length = -1;
        }
        if (character == EOF) {
            request[length] = '\0';
            send(client->sock, request, sizeof(request), 0);
            break;
        }
    }
    return client_listen(client);
}