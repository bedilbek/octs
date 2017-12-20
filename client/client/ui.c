//
// Created by shakhobiddin on 12/13/17.
//

#include <sys/file.h>
#include <unistd.h>
#include <helpers.h>
#include "ui.h"


const char *USR_FILE_NAME = "./usr_octs.txt";//"/Users/tom1/Documents/Subject files/OS/Project/octs/client/usr_octs.txt";

void print_line(int number) {
    for (int i = 0; i < number; i++)
        printf("-");
    printf("\n");
}

int isLoggedIn() {
    if (access(USR_FILE_NAME, F_OK) != -1)
        return 1;
    else return 0;
}

char *getToken() {
    FILE *f;
    char *token;
    token = malloc(75);

    f = fopen(USR_FILE_NAME, "r");
    fscanf(f, "%s", token);

    return token;
}

void logoutFunction() {
    remove(USR_FILE_NAME);
}

cJSON *loginMenu() {
    char *login;
    char *password;
    cJSON *lp = cJSON_CreateObject();

    login = (char *) malloc(60);
    password = (char *) malloc(60);

    printf("*********LOGIN MENU*********\n");
    printf("Username: ");
    scanf("%s", login);
    printf("Password: ");
    scanf("%s", password);

    cJSON_AddStringToObject(lp, "username", login);
    cJSON_AddStringToObject(lp, "password", password);
    return lp;
}

void show_contest(cJSON *contest) {
    char *id = "Contest ID";
    char *title = "Title";
    char *author = "Author";
    char *starts_at = "starts_at";
    char *ends_at = "ends_at";
    char *description = "Description";
    print_line(192);
    printf("%-12s|%-35s|%-30s|%-30s|%-30s|%-50s|\n", id, title, author, starts_at, ends_at, description);
    print_line(192);
    printf("      %-6d|", (int) get_attr(contest, "id", INTEGER));
    printf(" %-34s|", (char *) get_attr(contest, "title", STRING));
    printf("%-30s|", (char *) get_attr(contest, "author", STRING));
    printf("%-30s|", (char *) get_attr(contest, "starts_at", STRING));
    printf("%-30s|", (char *) get_attr(contest, "ends_at", STRING));
    printf("%-50s|", (char *) get_attr(contest, "description", STRING));
    printf("\n");
    print_line(192);
}

void show_problem(cJSON *problem) {
    print_line(192);
    printf("Problem ID: %d\n", (int) get_attr(problem, "id", INTEGER));
    printf("Title: %s\n", (char *) get_attr(problem, "title", STRING));
    printf("Category: %s\n", (char *) get_attr(problem, "category", STRING));
    printf("Description: %s\n", (char *) get_attr(problem, "description", STRING));
    printf("Time limit: %d\n", (int) get_attr(problem, "time_limit", INTEGER));
    printf("Memory limit: %d\n", (int) get_attr(problem, "memory_limit", INTEGER));
    printf("Max points: %d", (int) get_attr(problem, "max_points", INTEGER));
    printf("\n");
    print_line(192);
}

//struct User{
//    char fname[100];
//    char lname[100];
//    char token[100];
//    int id;
//};

void makeUser() {// NOT COMPLETED
//    char *fname;
//    char *lname;
//    char *token;
//    int id;
//    int i=0;
//    char *buff[10];
//  //  struct User u;
//    f = fopen(USR_FILE_NAME, "r");
//
//    while(fscanf(f, "%s", buff[i])!=EOF){
//        i++;
//    }
//
//    printf("%s\n", fname);
//    printf("%s", lname);
//    fclose(f);
//
//    //return u;

}

void saveToFileOcts(char *token) {
    FILE *f;

    f = fopen(USR_FILE_NAME, "w");

    fprintf(f, "%s", token);
    //rewind(f);
    fclose(f);
}

cJSON *signup() // for registering a new user it should have CLIENT attritbute
{
    char *fname;
    char *lname;
    char *mail;
    char *login;
    char *password;
    int responseStatus;
    char *responseMsg;

    cJSON *response = cJSON_CreateObject();
    cJSON *regData = cJSON_CreateObject();

    fname = (char *) malloc(100);
    lname = (char *) malloc(100);
    mail = (char *) malloc(100);
    login = (char *) malloc(100);
    password = (char *) malloc(100);

    printf("*********Register Menu*********\n");

    printf("First Name:\t");
    scanf("%s", fname);

    printf("Last Name:\t");
    scanf("%s", lname);

    printf("E-mail:\t\t");
    scanf("%s", mail);

    printf("Username:\t");
    scanf("%s", login);

    printf("Password:\t");
    scanf("%s", password);


    cJSON_AddStringToObject(regData, "fname", fname);
    cJSON_AddStringToObject(regData, "lname", lname);
    cJSON_AddStringToObject(regData, "email", mail);
    cJSON_AddStringToObject(regData, "username", login);
    cJSON_AddStringToObject(regData, "password", password);
    return regData;
}

void showContests(cJSON *contests, int size)// lists all the available contests
{
    int i = 0;
    char *id = "Contest_ID";
    char *title = "Title";
    char *starts_at = "Starts_at";
    char *ends_at = "Ends_at";
    char *reg_end_time = "Registration ends";
    print_line(141);
    printf("%-12s|%-35s|%-30s|%-30s|%-30s|\n", id, title, starts_at, ends_at, reg_end_time);
    print_line(141);
    for (i = 0; i < size; i++) {
        cJSON *contest = cJSON_GetArrayItem(contests, i);
        printf("   %-9d|", (int) get_attr(contest, "id", INTEGER));
        printf(" %-34s|", (char *) get_attr(contest, "title", STRING));
        printf("%-30s|", (char *) get_attr(contest, "starts_at", STRING));
        printf("%-30s|", (char *) get_attr(contest, "ends_at", STRING));
        printf("%-30s|", (char *) get_attr(contest, "reg_end_time", STRING));
        printf("\n");
        print_line(141);
    }
}

void show_problems(cJSON *problems) {
    int size = cJSON_GetArraySize(problems);
    int i = 0;
    char *id = "Problem_id";
    char *title = "Category";
    char *starts_at = "Time limit";
    char *ends_at = "Memory limit";
    char *reg_end_time = "Max point";
    print_line(141);
    printf("%-12s|%-35s|%-30s|%-30s|%-30s|\n", id, title, starts_at, ends_at, reg_end_time);
    print_line(141);
    for (i = 0; i < size; i++) {
        cJSON *contest = cJSON_GetArrayItem(problems, i);
        printf("   %-9d|", (int) get_attr(contest, "id", INTEGER));
        printf(" %-34s|", (char *) get_attr(contest, "name", STRING));
        printf("%-30d|", (int) get_attr(contest, "time_limit", INTEGER));
        printf("%-30d|", (int) get_attr(contest, "memory_limit", INTEGER));
        printf("%-30d|", (int) get_attr(contest, "max_points", INTEGER));
        printf("\n");
        print_line(141);
    }
}

cJSON *getProblemFromUser() {
    char title[1024], description[1024], input_file_path[1024] = {}, output_file_path[1024] = {};
    int category_id, time_limit, memory_limit, max_points;
    char c;
    printf("Title: ");
    fgets(title, 1024, stdin);

    printf("Category ID: ");
    scanf("%d", &category_id);
    scanf("%c", &c);

    printf("Description: ");
    fgets(description, 1024, stdin);

    printf("Input file path(absolute): ");
    fgets(input_file_path, 1024, stdin);
    input_file_path[strlen(input_file_path) - 1] = '\0';

    printf("Output file path(absolute): ");
    fgets(output_file_path, 1024, stdin);
    output_file_path[strlen(output_file_path) - 1] = '\0';

    printf("Time limit: ");
    scanf("%d", &time_limit);
    scanf("%c", &c);

    printf("Memory limit: ");
    scanf("%d", &memory_limit);
    scanf("%c", &c);

    printf("Max points: ");
    scanf("%d", &max_points);
    scanf("%c", &c);

    cJSON *params = cJSON_CreateObject();
    cJSON_AddStringToObject(params, "title", title);
    cJSON_AddNumberToObject(params, "category_id", category_id);
    cJSON_AddStringToObject(params, "description", description);
    cJSON_AddStringToObject(params, "input_file_path", input_file_path);
    cJSON_AddStringToObject(params, "output_file_path", output_file_path);
    cJSON_AddNumberToObject(params, "time_limit", time_limit);
    cJSON_AddNumberToObject(params, "memory_limit", memory_limit);
    cJSON_AddNumberToObject(params, "max_points", max_points);
    return params;
}

void show_results(cJSON *results) {
    int size = cJSON_GetArraySize(results);
    print_line(87);
    printf("%-20s|%-35s|%-30s|\n", "Trial number", "Points", "Status");
    print_line(87);
    for (int i = 0; i < size; i++) {
        cJSON *result = cJSON_GetArrayItem(results, i);
        printf("     %-15d|", (int) get_attr(result, "trial_number", INTEGER));
        printf(" %-34d|", (int) get_attr(result, "points", INTEGER));
        switch ((int) get_attr(result, "success", INTEGER)) {
            case TEST_CASE_OK:
                printf("%-30s|", "Passed");
                break;
            case COMPILATION_ERROR:
                printf("%-30s|", "Compilation error");
                break;
            case TEST_CASE_FAILED:
                printf("%-30s|", "Test case failed");
                break;
            case TEST_CASES_SUCCESS:
                printf("%-30s|", "Passed");
                break;
            case TEST_CASES_UNDEFINED_ERROR:
                printf("%-30s|", "Test cases are not valid");
                break;
            case TEST_CASE_TIME_LIMIT:
                printf("%-30s|", "Time limit is exceeded");
                break;
            default:
                printf("%-30s|", "Internal error");
        }
        printf("\n");
        print_line(87);
    }
}

cJSON *get_files() {
    char input_file_path[1024] = {}, output_file_path[1024] = {};
    printf("Input file path(absolute): ");
    fflush(stdout);
    fgets(input_file_path, 1024, stdin);
    input_file_path[strlen(input_file_path) - 1] = '\0';

    printf("Output file path(absolute): ");
    fflush(stdout);
    fgets(output_file_path, 1024, stdin);
    output_file_path[strlen(output_file_path) - 1] = '\0';

    cJSON *params = cJSON_CreateObject();
    cJSON_AddStringToObject(params, "input_file_path", input_file_path);
    cJSON_AddStringToObject(params, "output_file_path", output_file_path);
    return params;
}

cJSON *create_contest() {
    cJSON *data = cJSON_CreateObject();
    char title[1024] = {}, description[1024] = {}, starts_at[1024] = {},
            ends_at[1024] = {}, register_time[1024] = {}, end_register_time[1024] = {};
    char c;
    printf("Enter title: ");
    fgets(title, 1024, stdin);
    title[strlen(title) - 1] = '\0';

    printf("Description: ");
    fgets(description, 1024, stdin);
    description[strlen(description) - 1] = '\0';

    printf("Starts at: ");
    fgets(starts_at, 1024, stdin);
    starts_at[strlen(starts_at) - 1] = '\0';

    printf("Ends at: ");
    fgets(ends_at, 1024, stdin);
    ends_at[strlen(ends_at) - 1] = '\0';

    printf("Register start time: ");
    fgets(register_time, 1024, stdin);
    register_time[strlen(register_time) - 1] = '\0';

    printf("Register end time: ");
    fgets(end_register_time, 1024, stdin);
    end_register_time[strlen(end_register_time) - 1] = '\0';

    cJSON_AddStringToObject(data, "title", title);
    cJSON_AddStringToObject(data, "description", description);
    cJSON_AddStringToObject(data, "starts_at", starts_at);
    cJSON_AddStringToObject(data, "ends_at", ends_at);
    cJSON_AddStringToObject(data, "reg_start_time", register_time);
    cJSON_AddStringToObject(data, "reg_end_time", end_register_time);
    return data;
}