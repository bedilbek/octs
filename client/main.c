////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include <tic.h>
#include "ui.h"
#include "client.h"
#include "client_methods.h"

void print_table_TEST() {
    char *id = "Contest_ID";
    char *title = "Title";
    char *starts_at = "Starts_at";
    char *ends_at = "Ends_at";
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s|%-35s|%-15s|\n", id, title, starts_at, ends_at, "reg_end_date");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < 5; i++) {
        printf("   %-9d|", (i + 3) * 1232);
        printf("%-35s|", "Quadratic equation");
        printf("%-15s|", "45-45-1997 12:30");
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------------------------------\n");
    }

}


int main(int argc, char *argv[]) {
    //    cJSON *params = cJSON_CreateObject();
//    cJSON_AddStringToObject(params, "name", "Shoh");
//    printf((char *)cJSON_parser(cJSON_GetObjectItem(params, "name")));


    //struct Client *client = new(Client, SERVER_LISTEN_PORT);
    //cJSON_AddNumberToObject(params, "id", 123);
    // cJSON *response = (cJSON *) send_message(client, "get_user", params);
    //  struct User u;
//    makeUser();
    // saveToFileOcts("qwertyyfflghdfjgkdjlf564456564");
    // registerMenu();
    //loginMenu();
    //print_table_TEST();
//    getProblemFromUser();
//    struct Client *client = new(Client, SERVER_LISTEN_PORT);
//    struct Client *file_client= new(Client, FILE_SERVER_LISTEN_PORT);
//    else if(argc == 3 && strcmp(argv[1],"apply"))
//    {
//        int contest_id = argv[2];
//        char *token;
//        if(isLoggedIn())
//        {
//            token = getToken();
//            cJSON *apply = cJSON_CreateObject();
//            cJSON_AddStringToObject(apply,"token",token);
//            cJSON_AddNumberToObject(apply,"contest_id",contest_id);
//            cJSON *response;
//            response = (cJSON *) send_message(client, 4 , apply);
//            int status = cJSON_GetObjectItem("status",response);
//            if(status == 200 || status == 201)
//            {
//
//                char *message = cJSON_GetObjectItem("message",response);
//                printf(message);
//            } else
//            {
//                char *err_msg = cJSON_GetObjectItem("err_msg",response);
//                printf(err_msg);
//            }
//        }
//        else
//        {
//            printf("You haven't logged in\n");
//        }
//
//
//
//    }
//    else if(argc == 4 && strcmp(argv[1],"ls") && strcmp(argv[2],"problem"))
//    {
//        int problem_id = argv[3];
//        /*
//         * 1. login is checked
//         * 2. problems description is received from server
//         * 3. here some function will display description
//        */
//        if(isLoggedIn())
//        {
//            char *token = getToken();
//            cJSON *problem = cJSON_CreateObject();
//            cJSON_AddStringToObject(problem,"token",token);
//            cJSON_AddStringToObject(problem,"problem_id",problem_id);
//            cJSON *response;
//            response = (cJSON *) send_message(client, 4 , problem);
//
//            int status = cJSON_GetObjectItem(response,"status")->valueint;
//            if(status == 200)
//            {
//
//                cJSON *problemDetails = cJSON_GetObjectItem(response,"data");
//                showProblemetails(problemDetails);
//            }
//            else
//            {
//                char *message = cJSON_GetObjectItem(response,"err_msg")->valuestring;
//                printf(message);
//            }
//
//        }
//        else
//        {
//            printf("You haven't logged in yet");
//        }
//    }
//    else if(argc == 3 && strcmp(argv[1],"create") && (strcmp(argv[2],"problem") || strcmp(argv[2],"-p")))
//    {
//        cJSON *newProblem;
//
//        if(isLoggedIn())
//        {
//            char *token = getToken();
//            newProblem = getProblemFromUser(); /*this function returns the new problem's cJSON object*/
//            char *path1 = cJSON_GetObjectItem(newProblem, "absolute_path1")->valuestring;
//            char *path2 = cJSON_GetObjectItem(newProblem, "absolute_path2")->valuestring;
//            int file1_id, file2_id;
//            int stat;
//            cJSON *response;
//            cJSON *responseForFile1 = send_file(file_client, token, path);
//            cJSON *responseForFile2 = send_file(file_client, token, path);
//
//            if(!(status=get_attr(response, "status", INTEGER))==200)
//            {
//                printf(get_attr(response, "err_msg", STRING));
//            }
//            else
//            {
//
//                file1_id = get_attr(responseForFile1, "file_id", INTEGER);
//                file2_id = get_attr(responseForFile2, "file_id", INTEGER);
//                cJSON_AddNumberToObject(newProblem, "input_file_id", file1_id);
//                cJSON_AddNumberToObject(newProblem, "output_file_id", file2_id);
//
//                response = send_message(client, CREATE_PROBLEM/*method number*/, newProblem);
//                stat = cJSON_GetObjectItem(response, "status");
//                if(stat==200 || stat==201)
//                {
//                    printf(cJSON_GetObjectItem(response, "message"));
//                    printf("The problem has successfully created\n");
//                }
//                else
//                {
//                    printf(cJSON_GetObjectItem(response, "err_msg"));
//                }
//            }
//        }
//        else
//        {
//            printf("You haven't logged in!");
//        }
//    }
//    else if(argc == 3 && strcmp(argv[1],"create") && (strcmp(argv[2],"contest") || strcmp(argv[2],"-c")))
//    {
//
//
//
//    }
    struct Client *message_client = new(Client, SERVER_LISTEN_PORT);
    struct Client *file_client = new(Client, FILE_SERVER_LISTEN_PORT);
    switch (argc) {
        case 2:
            if ((strcmp(argv[1], "login") == 0 || strcmp(argv[1], "Login") == 0)) // OCTS Login
            {
                login(message_client);
            }
            if (strcmp(argv[1], "register") == 0) {
                cJSON *request = registerMenu();
                register_user(message_client, request);
            }
            if (strcmp(argv[1], "logout") == 0) // OCTS logout
            {
                if (isLoggedIn()) {
                    logoutFunction(); // logout function just deletes the file with the token of the current user
                    printf("You logged out successfully \n"); // print to user that he/she logged out
                } else {
                    printf("You haven't logged in yet!\n");
                }
            }
            if (strcmp(argv[1], "contests") == 0 || strcmp(argv[1], "-c") == 0) // OCTS see all contest of user
            {
                if (isLoggedIn()) {
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), 3, NULL);
                    int status;
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 200) {
                        int size = cJSON_GetArraySize(cJSON_GetObjectItem(response, "data"));
                        showContests(cJSON_GetObjectItem(response, "data"), size);
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                } else {
                    printf("You haven't logged in yet\n");
                }
            }

            break;
        case 4:
            if (strcmp(argv[1], "ls") == 0 && (strcmp(argv[2], "contest") == 0 || strcmp(argv[2], "-c") == 0)) {
                if (isLoggedIn()) {
                    /*
                 * 1. login is checked
                 * 2. then it is check whether the user is in the contest
                 * 3. problems list is received from server
                 * 4. here the showContestProblems(cjson) function will display problems
                */
                    int contest_id = (int) strtol(argv[3], NULL, 10);
                    cJSON *contest = cJSON_CreateObject();
                    cJSON_AddNumberToObject(contest, "contest_id", contest_id);

                    cJSON *response = (cJSON *) send_message(message_client, getToken(), 4, contest);
                    int status;
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 200) {
                        int size = cJSON_GetArraySize(get_attr(response, "data", CJSON));
                        showContestProblems(get_attr(response, "data", CJSON), size);
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                } else {
                    printf("You haven't logged in yet\n");
                }
            }
            break;
        case 5:
            if (strcmp(argv[1], "submit") == 0) {
                if (isLoggedIn()) {
                    int contest_id = (int) strtol(argv[3], NULL, 10);
                    int problem_id = (int) strtol(argv[4], NULL, 10);
                    submit_solution(file_client, message_client, getToken(), argv[2], contest_id, problem_id);
                }
            }
            break;
        default:
            break;
    }
    free(message_client);
    free(file_client);
}
/*
 * $octs register
 * octs submit main.c
 * OK
 * octs show-result
octs //commands for user
	register - register()
	login - login()
    contests - contests()
    apply contest_id - applyForContest(contes_id)
    problems - showProblems()
    description problem_id -
    standings contest_id - showStandings(contest_id)

    submit file problem_id  - submit(argv[1], argv[2])



	--problems
	--see problem problem_id
octs //commands for admin
	--add new problem
	--submissions
	--problems
	--create contest
*/

//login - login
