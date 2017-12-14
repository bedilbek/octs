//
// Created by Tolqinbek Isoqov on 12/12/17.
//


#include "server.h"
#include "controllers.h"
#include "model.h"

int authenticate_user(char *token) {
    cJSON *result_user = get_user_by_token(token);
    int user_id = 0;
    if (!(user_id = (int) get_attr(cJSON_GetArrayItem(cJSON_GetObjectItem(result_user, "data"), 0), "id", INTEGER)))
        return 0;
    return user_id;
}

void return_response(int socket, cJSON *response) {
    char *response_message = cJSON_Print(response);
    send(socket, response_message, strlen(response_message), 0);
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
    char *token;
    int length;
    char *ext;
    if (!(token = get_attr(message, "token", STRING))) {
        cJSON *response = error_input("Login in order to proceed this operation");
        return_response(peer_socket, response);
        close(peer_socket);
        return;
    }
    if (!(length = (int) get_attr(message, "length", INTEGER))) {
        cJSON *response = error_input("length is required");
        return_response(peer_socket, response);
        close(peer_socket);
    }

    if (!(ext = get_attr(message, "ext", STRING))) {
        cJSON *response = error_input("ext is required");
        return_response(peer_socket, response);
        close(peer_socket);
    }

    int user_id;
    if (!(user_id = authenticate_user(token))) {
        cJSON *response = cJSON_CreateObject();
        setStatus(response, 403);
        setErrMsg(response, "Login in order to proceed this operation");
        return_response(peer_socket, response);
        close(peer_socket);
    }
    cJSON *request = cJSON_CreateObject();
    cJSON_AddNumberToObject(request, "user_id", user_id);
    cJSON_AddStringToObject(request, "ext", ext);

    //TODO validate above values
    for (int i = 0; i < sizeof(buffer); ++i) {
        buffer[i] = '\0';
    }
    file_size = length;

    char absolute_file_path[1024] = FILE_STORAGE;
    strcat(absolute_file_path, ext);
    int fd = mkstemps(absolute_file_path, (size_t) 4);

    received_file = fdopen(fd, "w");
    if (received_file == NULL) {
        return;
    }
    printf(absolute_file_path);
    cJSON_AddStringToObject(request, "absolute_path", absolute_file_path);

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

    cJSON *response = methods[0](request);
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
