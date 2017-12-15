//
// Created by Tolqinbek Isoqov on 12/15/17.
//

#include "client_methods.h"
#include "ui.h"

void login(struct Client *client) {
    cJSON *responseLogin;
    cJSON *loginDetails;

    if (!isLoggedIn()) // isLoggedIn function checks whether there is a file with token
    {
        int status;
        loginDetails = loginMenu(); // call Login menu function (username , password)

        responseLogin = (cJSON *) send_message(client, NULL, 0, loginDetails);
        status = cJSON_GetObjectItem(responseLogin, "status")->valueint;
        if (status == 200 || status == 201) {
            char *token = cJSON_GetObjectItem(responseLogin, "token")->valuestring; // token of user
            saveToFileOcts(token); // save name lastname and token with id in .octs
            printf("Successfully Logged In");
        } else {
            char *error = cJSON_GetObjectItem(responseLogin, "err_msg")->valuestring;
            printf(error);
        }
    } else {
        printf("You have already signed in!\n");
    }

}