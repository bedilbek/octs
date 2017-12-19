#include "ui.h"
#include "client.h"
#include "client_methods.h"

#define NONE "-"


int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    struct Client *message_client = new(Client, SERVER_LISTEN_PORT);
    switch (argc) {
        case 2:
            if ((strcmp(argv[1], "login") == 0 || strcmp(argv[1], "Login") == 0)) // OCTS Login
            {
                login(message_client);
            }
            if (strcmp(argv[1], "signup") == 0) {
                if (!isLoggedIn()) {
                    cJSON *request = signup();
                    register_user(message_client, request);
                } else {
                    printf("You have already logged in. In order to create user please logout\n");
                }
            }
            if (strcmp(argv[1], "logout") == 0) {
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
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), GET_CONTESTS, NULL);
                    if ((int) get_attr(response, "status", INTEGER) == 200) {
                        int size = cJSON_GetArraySize(get_attr(response, "data", CJSON));
                        showContests(get_attr(response, "data", CJSON), size);
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                } else {
                    printf("You haven't logged in yet\n");
                }
            }

            break;
        case 3:
            if (strcmp(argv[1], "contest") == 0 || strcmp(argv[1], "-c") == 0) {
                if (isLoggedIn()) {
                    int contest_id = (int) strtol(argv[2], NULL, 10);
                    cJSON *request = cJSON_CreateObject();
                    cJSON_AddNumberToObject(request, "contest_id", contest_id);
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), GET_CONTEST, request);
                    int status;
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 200) {
                        show_contest(cJSON_GetArrayItem(get_attr(response, "data", CJSON), 0));
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                } else {
                    printf("You haven't logged in\n");
                }
            }
            if (strcmp(argv[1], "create") == 0 && strcmp(argv[2], "contest") == 0) {
                if (isLoggedIn()) {
                    cJSON *request = create_contest();
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), CREATE_CONTEST, request);
                    if ((int) get_attr(response, "status", INTEGER) == 201) {
                        printf("Successfully created");
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                } else {
                    printf("You haven't logged in\n");
                }
            }
            if (strcmp(argv[1], "my") == 0 && (strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "contests") == 0)) {
                if (isLoggedIn()) {
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), MY_CONTESTS, NULL);
                    int status;
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 200) {
                        int size = cJSON_GetArraySize(get_attr(response, "data", CJSON));
                        showContests(get_attr(response, "data", CJSON), size);
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                } else {
                    printf("You haven't logged in\n");
                }
            }
            if (strcmp(argv[1], "problems") == 0 || strcmp(argv[1], "-p") == 0) {
                if (isLoggedIn()) {
                    int problem_id = (int) strtol(argv[2], NULL, 10);
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), GET_PROBLEMS, NULL);
                    if (((int) get_attr(response, "status", INTEGER)) == 200) {
                        show_problems(get_attr(response, "data", CJSON));
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                } else {
                    printf("You haven't logged in\n");
                }
            }
            if (strcmp(argv[1], "create") == 0 && (strcmp(argv[2], "problem") == 0 || strcmp(argv[2], "-p") == 0)) {
                if (isLoggedIn()) {
                    struct Client *file_client = new(Client, FILE_SERVER_LISTEN_PORT);
                    cJSON *new_problem = getProblemFromUser(); /*this function returns the new problem's cJSON object*/
                    char *input_file_path = get_attr(new_problem, "input_file_path", STRING);
                    char *output_file_path = get_attr(new_problem, "output_file_path", STRING);
                    int status;

                    cJSON *input_file_response = send_file(file_client, getToken(), input_file_path);
                    if ((status = (int) get_attr(input_file_response, "status", INTEGER)) != 201) {
                        printf("Error in input_file uploading");
                        return -1;
                    }
                    free(file_client);
                    file_client = new(Client, FILE_SERVER_LISTEN_PORT);
                    cJSON *output_file_response = send_file(file_client, getToken(), output_file_path);
                    if ((status = (int) get_attr(output_file_response, "status", INTEGER)) != 201) {
                        printf("Error in output_file uploading");
                        return -1;
                    }
                    free(file_client);
                    int input_file = (int) get_attr(input_file_response, "file_id", INTEGER);
                    int output_file = (int) get_attr(output_file_response, "file_id", INTEGER);
                    cJSON_AddNumberToObject(new_problem, "input_file_id", input_file);
                    cJSON_AddNumberToObject(new_problem, "output_file_id", output_file);
                    cJSON *response = send_message(message_client, getToken(), PROBLEM_CREATION, new_problem);
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 201) {
                        printf("The problem has successfully created\n");
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }
                    close(file_client->sock);
                } else {
                    printf("You haven't logged in!");
                }
            }
            break;
        case 4:
            if (strcmp(argv[1], "ls") == 0 && (strcmp(argv[2], "contest") == 0 || strcmp(argv[2], "-c") == 0)) {
                if (isLoggedIn()) {
                    int contest_id = (int) strtol(argv[3], NULL, 10);
                    cJSON *request = cJSON_CreateObject();
                    cJSON_AddNumberToObject(request, "contest_id", contest_id);
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), GET_CONTEST_PROBLEMS, request);

                    int status;
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 200) {
                        cJSON *contest_problems = get_attr(response, "data", CJSON);
                        int size = cJSON_GetArraySize(contest_problems);
                        show_problems(contest_problems);
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }

                } else {
                    printf("You haven't logged in yet");
                }
            }
            if (strcmp(argv[1], "detail") == 0 && (strcmp(argv[2], "problem") == 0 || strcmp(argv[2], "-p") == 0)) {
                if (isLoggedIn()) {
                    int problem_id = (int) strtol(argv[3], NULL, 10);
                    cJSON *request = cJSON_CreateObject();
                    cJSON_AddNumberToObject(request, "problem_id", problem_id);
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), GET_PROBLEM, request);

                    int status;
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 200) {
                        cJSON *problem = cJSON_GetArrayItem(get_attr(response, "data", CJSON), 0);
                        show_problem(problem);
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }

                } else {
                    printf("You haven't logged in yet");
                }
            }
            if (strcmp(argv[1], "register") == 0 && (strcmp(argv[2], "contest") == 0 || strcmp(argv[2], "-c") == 0)) {
                if (isLoggedIn()) {
                    int contest_id = (int) strtol(argv[3], NULL, 10);
                    cJSON *request = cJSON_CreateObject();
                    cJSON_AddNumberToObject(request, "contest_id", contest_id);
                    cJSON *response = (cJSON *) send_message(message_client, getToken(), REGISTER_FOR_CONTEST, request);
                    int status;
                    if ((status = (int) get_attr(response, "status", INTEGER)) == 201) {
                        printf("Successfully registered for contest");
                    } else {
                        printf(get_attr(response, "err_msg", STRING));
                    }

                } else {
                    printf("You haven't logged in yet");
                }
            }
            if (strcmp(argv[1], "submit") == 0) {
                if (isLoggedIn()) {
                    struct Client *file_client = new(Client, FILE_SERVER_LISTEN_PORT);
                    int contest_id = (int) strtol(argv[2], NULL, 10);
                    int problem_id = (int) strtol(argv[3], NULL, 10);
                    char path[1024] = {};
                    printf("Enter file path: ");
                    fgets(path, 1024, stdin);
                    path[strlen(path) - 1] = '\0';
                    submit_solution(file_client, message_client, getToken(), path, contest_id, problem_id);
                }
            }
            break;
        case 5:
            if (strcmp(argv[1], "show") == 0 && strcmp(argv[2], "result") == 0) {
                if (isLoggedIn()) {
                    int contest_id = (int) strtol(argv[3], NULL, 10);
                    int problem_id;
                    if (argv[4] != NONE) {
                        problem_id = (int) strtol(argv[4], NULL, 10);
                    } else {
                        problem_id = -1;
                    }
                    cJSON *request = cJSON_CreateObject();
                    cJSON_AddNumberToObject(request, "contest_id", contest_id);
                    cJSON_AddNumberToObject(request, "problem_id", problem_id);
                    cJSON *response = send_message(message_client, getToken(), CHECK_RESULT, request);
                    if ((int) get_attr(response, "status", INTEGER) != 200) {
                        printf(get_attr(response, "err_msg", STRING));
                        return 1;
                    }
                    show_results(get_attr(response, "data", CJSON));
                }
            }
            if (strcmp(argv[1], "add") == 0 && strcmp(argv[2], "problem") == 0) {
                if (isLoggedIn()) {
                    int contest_id = (int) strtol(argv[3], NULL, 10);
                    int problem_id;
                    problem_id = (int) strtol(argv[4], NULL, 10);
                    cJSON *request = cJSON_CreateObject();
                    cJSON_AddNumberToObject(request, "contest_id", contest_id);
                    cJSON_AddNumberToObject(request, "problem_id", problem_id);
                    cJSON *response = send_message(message_client, getToken(), ADD_PROBLEM_TO_CONTEST, request);
                    if ((int) get_attr(response, "status", INTEGER) != 201) {
                        printf(get_attr(response, "err_msg", STRING));
                        return 1;
                    }
                    printf("Problem is added to contest");
                }
            }
            if (strcmp(argv[1], "create") == 0 && strcmp(argv[2], "test") == 0 && strcmp(argv[3], "case") == 0) {
                if (isLoggedIn()) {
                    struct Client *file_client = new(Client, FILE_SERVER_LISTEN_PORT);

                    int problem_id = (int) strtol(argv[4], NULL, 10);
                    cJSON *request = cJSON_CreateObject();
                    cJSON *files = get_files();
                    char *input_file_path = get_attr(files, "input_file_path", STRING);
                    char *output_file_path = get_attr(files, "output_file_path", STRING);
                    cJSON *input_file_response = send_file(file_client, getToken(), input_file_path);
                    if (((int) get_attr(input_file_response, "status", INTEGER)) != 201) {
                        printf(get_attr(input_file_response, "err_msg", STRING));
                        return -1;
                    }
                    free(file_client);
                    file_client = new(Client, FILE_SERVER_LISTEN_PORT);
                    cJSON *output_file_response = send_file(file_client, getToken(), output_file_path);
                    if (((int) get_attr(output_file_response, "status", INTEGER)) != 201) {
                        printf(get_attr(output_file_response, "err_msg", STRING));
                        return -1;
                    }
                    free(file_client);
                    char explanation[1024] = {};
                    printf("Explanation: ");
                    fgets(explanation, 1024, stdin);
                    int input_file = (int) get_attr(input_file_response, "file_id", INTEGER);
                    int output_file = (int) get_attr(output_file_response, "file_id", INTEGER);
                    cJSON_AddNumberToObject(request, "problem_id", problem_id);
                    cJSON_AddNumberToObject(request, "input_file_id", input_file);
                    cJSON_AddNumberToObject(request, "output_file_id", output_file);
                    cJSON_AddStringToObject(request, "explanation", explanation);
                    cJSON *response = send_message(message_client, getToken(), CREATE_TEST_CASE, request);
                    if ((int) get_attr(response, "status", INTEGER) != 201) {
                        printf(get_attr(response, "err_msg", STRING));
                        return 1;
                    }
                    printf("Test case is successfully created");
                }
            }
            break;
        default:
            break;
    }
    free(message_client);
}
