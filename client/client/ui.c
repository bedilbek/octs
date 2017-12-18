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
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s|%-35s|%-30s|%-30s|%-30s|\n", id, title, starts_at, ends_at, reg_end_time);
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < size; i++) {
        cJSON *contest = cJSON_GetArrayItem(contests, i);
        printf("   %-9d|", (int) get_attr(contest, "id", INTEGER));
        printf(" %-34s|", (char *) get_attr(contest, "title", STRING));
        printf("%-30s|", (char *) get_attr(contest, "starts_at", STRING));
        printf("%-30s|", (char *) get_attr(contest, "ends_at", STRING));
        printf("%-30s|", (char *) get_attr(contest, "reg_end_time", STRING));
        printf("\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}

void showContestProblems(cJSON *problems, int size)//lists all the problems of a contest
{
    char *id = "Problem_ID";
    char *title = "Title";
    char *max_points = "Max_Points";
    int i = 0;
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s|%-20s|%-20s|\n", id, title, max_points);
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < size; i++) {
        printf("   %-9d", cJSON_GetObjectItem(cJSON_GetArrayItem(problems, i), "id")->valueint);
        printf("%-20s", cJSON_GetObjectItem(cJSON_GetArrayItem(problems, i), "title")->valuestring);
        printf("%-15d", cJSON_GetObjectItem(cJSON_GetArrayItem(problems, i), "max_points")->valueint);
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------------------------------\n");
    }

}

void show_contest_problems(cJSON *problems, int size) {
    //TODO: not correct function
    int i = 0;
    char *id = "Problem_id";
    char *title = "Category";
    char *starts_at = "Time limit";
    char *ends_at = "Memory limit";
    char *reg_end_time = "Max point";
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s|%-35s|%-30s|%-30s|%-30s|\n", id, title, starts_at, ends_at, reg_end_time);
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < size; i++) {
        cJSON *contest = cJSON_GetArrayItem(problems, i);
        printf("   %-9d|", (int) get_attr(contest, "id", INTEGER));
        printf(" %-34s|", (char *) get_attr(contest, "name", STRING));
        printf("%-30d|", (int) get_attr(contest, "time_limit", INTEGER));
        printf("%-30d|", (int) get_attr(contest, "memory_limit", INTEGER));
        printf("%-30d|", (int) get_attr(contest, "max_points", INTEGER));
        printf("\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
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