//
// Created by Tolqinbek Isoqov on 12/15/17.
//

#include "client_methods.h"
#include "ui.h"

void login(struct Client *client) {

    if (!isLoggedIn()) // isLoggedIn function checks whether there is a file with token
    {

        cJSON *login_credentials = loginMenu(); // call Login menu function (username , password)

        cJSON *response = (cJSON *) send_message(client, NULL, LOGIN, login_credentials);
        int status;
        if ((status = (int) get_attr(response, "status", INTEGER)) == 200) {
            char *token = get_attr(response, "token", STRING); // token of user
            saveToFileOcts(token); // save name lastname and token with id in .octs
            printf("Successfully Logged In");
        } else {
            printf(get_attr(response, "err_msgs", STRING));
        }
    } else {
        printf("You have already signed in!\n");
    }

}