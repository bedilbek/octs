//
// Created by Tolqinbek Isoqov on 12/15/17.
//

#include <client.h>

#ifndef OS_PROJECT_METHODS_H
#define OS_PROJECT_METHODS_H

void login(struct Client *client);

void signin(struct Client *client);

void submit_solution(struct Client *file_client, struct Client *message_client, char *token, char *path, int contest_id,
                     int problem_id);

void register_user(struct Client *client, cJSON *request);

#endif //OS_PROJECT_METHODS_H
