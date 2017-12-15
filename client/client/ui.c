//
// Created by shakhobiddin on 12/13/17.
//

#include "ui.h"



const char* USR_FILE_NAME = "usr_octs";

int isLoggedIn()
{
    if(access(USR_FILE_NAME, F_OK)!=-1)
    return 1;
    else return 0;
}

char *getToken()
{
    FILE *f;
    char *token;
    token = malloc(75);

    f = fopen(USR_FILE_NAME, "r");
    fscanf(f, "%s", token);

    return token;
}
void logoutFunction()
{
    remove(USR_FILE_NAME);
}

cJSON *loginMenu()
{
    char *login;
    char *password;
    cJSON *lp = cJSON_CreateObject();

    login = (char*)malloc(60);
    password = (char *)malloc(60);

    printf("*********LOGIN MENU*********\n");
    printf("Username: ");
    scanf("%s", login);
    printf("Password: ");
    scanf("%s", password);

    cJSON_AddStringToObject(lp, "username", login);
    cJSON_AddStringToObject(lp, "password", password);
    printf("%s", cJSON_Print(lp));
    return lp;
}



//struct User{
//    char fname[100];
//    char lname[100];
//    char token[100];
//    int id;
//};

void makeUser()
{// NOT COMPLETED
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

void saveToFileOcts(char *token)
{
    FILE *f;

    f = fopen(USR_FILE_NAME, "w");

    fprintf(f, "%s", token);
    //rewind(f);
    fclose(f);
}

void registerMenu(struct Client client) // for registering a new user it should have CLIENT attritbute
{
    char *fname;
    char *lname;
    char *mail;
    char *login;
    char *password;
    int responseStatus;
    char *responseMsg;

    cJSON *response =  cJSON_CreateObject();
    cJSON *regData = cJSON_CreateObject();

    fname = (char*)malloc(100);
    lname = (char*)malloc(100);
    mail = (char*)malloc(100);
    login = (char*)malloc(100);
    password = (char*)malloc(100);

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
    //client should be added
   // response = (cJSON*)send_message(client, 2, regData);// should be tested with server connection

    responseStatus = cJSON_GetObjectItem(response, "status")->valueint;
    responseMsg = cJSON_GetObjectItem(response, "message")->valuestring;// NOT FINISHED YET

    if(responseStatus==200 || responseStatus==201)
    {
        printf("You have successfully signed up\n");
        printf("%s", responseMsg);
    }
    else
    {
        printf("%s", responseMsg);
        printf("Smth went wrong\n Please try again");
    }

}

void showContests(cJSON *contests, int size)// lists all the available contests
{
    int i=0;
    char *id = "Contest_ID";
    char *title = "Title";
    char *starts_at = "Starts_at";
    char *ends_at = "Ends_at";
    char *reg_end_date = "Registration ends";
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s|%-35s|%-20s|%-20s|%-20s|\n", id, title, starts_at, ends_at, reg_end_date);
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    for(i=0; i<size;i++)
    {
        printf("   %-9d|", cJSON_GetObjectItem(cJSON_GetArrayItem(contests, i), "id")->valueint);
        printf(" %-34s|", cJSON_GetObjectItem(cJSON_GetArrayItem(contests, i), "title")->valuestring);
        printf("%-20s|", cJSON_GetObjectItem(cJSON_GetArrayItem(contests, i), "starts_at")->valuestring);
        printf("%-20s|", cJSON_GetObjectItem(cJSON_GetArrayItem(contests, i), "ends_at")->valuestring);
        printf("%-20s|", cJSON_GetObjectItem(cJSON_GetArrayItem(contests, i), "reg_end_at")->valuestring);
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------------------------------\n");
    }
}

void showContestProblems(cJSON *problems, int size)//lists all the problems of a contest
{
    char *id = "Problem_ID";
    char *title = "Title";
    char *max_points = "Max_Points";
    int i=0;
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s|%-20s|%-20s|\n", id, title, max_points);
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    for(i=0; i<size;i++)
    {
        printf("   %-9d", cJSON_GetObjectItem(cJSON_GetArrayItem(problems, i), "id")->valueint);
        printf("%-20s", cJSON_GetObjectItem(cJSON_GetArrayItem(problems, i), "title")->valuestring);
        printf("%-15d", cJSON_GetObjectItem(cJSON_GetArrayItem(problems, i), "max_points")->valueint);
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------------------------------\n");
    }

}


void showProblemDetails(cJSON *problem)
{
    printf("******************Problem Details******************");
    printf("Title: %s", cJSON_GetObjectItem(problem, "title")->valuestring);
    printf("\nDescription: %s", cJSON_GetObjectItem(problem, "description")->valuestring);
    printf("\nInput Format: %s", cJSON_GetObjectItem(problem, "input_format")->valuestring);
    printf("\nOutput Format: %s", cJSON_GetObjectItem(problem, "output_format")->valuestring);
    printf("\nTime Limit: %d sec", cJSON_GetObjectItem(problem, "time_limit")->valueint);
    printf("\nMemory Limit: %d MB", cJSON_GetObjectItem(problem, "memory_limit")->valueint);
    printf("\nMax points: %d sec", cJSON_GetObjectItem(problem, "max_points")->valueint);
}

cJSON *getProblemFromUser()
{
    char *title = (char*)malloc(256);
    title[59] = '\0';
    char *description = (char*)malloc(2048);
    description[2047] = '\0';
    char *inputPath = (char*)malloc(128);
    char *outputPath = (char*)malloc(128);
    int time_limit;
    int memory_limit;
    int max_points;
    cJSON *newProblem = cJSON_CreateObject();
    char c;
    printf("Title: ");
    fgets(title, 256, stdin);
//    scanf("%c", &c);
    printf("Description: ");
    fgets(description, 2048, stdin);

    //scanf ("%s", description);

    printf("Input file path(absolute): ");
    scanf("%s", inputPath);

    printf("Output file path(absolute): ");
    scanf("%s", outputPath);

    printf("Time Limit(seconds): ");
    scanf("%d", &time_limit);

    printf("Memory Limit(MBs): ");
    scanf("%d", &memory_limit);

    printf("Max_points: ");
    scanf("%d", &max_points);

    cJSON_AddStringToObject(newProblem, "title", title);
    cJSON_AddStringToObject(newProblem, "description", description);
    cJSON_AddStringToObject(newProblem, "input_file_path", inputPath);
    cJSON_AddStringToObject(newProblem, "output_file_path", outputPath);
    cJSON_AddNumberToObject(newProblem, "time_limit", time_limit);
    cJSON_AddNumberToObject(newProblem, "memory_limit", memory_limit);
    cJSON_AddNumberToObject(newProblem, "memory_limit", memory_limit);
    cJSON_AddNumberToObject(newProblem, "max_points", max_points);

    printf("%s\n", cJSON_Print(cJSON_GetObjectItem(newProblem, "title")));
    printf("%s\n", cJSON_Print(cJSON_GetObjectItem(newProblem, "description")));
    printf("%s\n", cJSON_Print(cJSON_GetObjectItem(newProblem, "input_file_path")));
    printf("%s\n", cJSON_Print(cJSON_GetObjectItem(newProblem, "output_file_path")));
    return newProblem;
}