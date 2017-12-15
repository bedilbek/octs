//
// Created by Tolqinbek Isoqov on 12/15/17.
//
#include "client_methods.h"

void register_user(struct Client *client, cJSON *request) {
    cJSON *response = (cJSON *) send_message(client, NULL, 2, request);
    int status;
    if ((status = get_attr(response, "status", INTEGER)) == 201) {
        printf("You have successfully signed up\n");
    } else {
        printf(get_attr(response, "err_msg", STRING));
    }
}