//
// Created by shakhobiddin on 12/13/17.
//

#include "ui.h"



const char* USR_FILE_NAME = "usr_octs";

int isLoggedIn()
{
    FILE *f;
    char *buff;

    f = fopen(USR_FILE_NAME, "r");

    return fscanf(f, "%s", buff);

}


cJSON *loginMenu()
{
    char *login;
    char *password;
    cJSON *lp;
    printf("*********LOGIN MENU*********\n");
    printf("Username: ");
    scanf("%s", login);
    printf("Password: ");
    scanf("%s", password);

    cJSON_AddStringToObject(lp, "username", login);
    cJSON_AddStringToObject(lp, "password", password);

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

void saveToFileOcts(char *fname, char *lname, char *token, int id)
{
    FILE *f;

    f = fopen(USR_FILE_NAME, "w");

    fprintf(f, "%s %s %s %d", fname, lname, token, id);
    rewind(f);
    fclose(f);
}

void registerMenu() // for registering a new user
{


}

void showContests(cJSON *contests)// lists all the available contests
{




}

void showContestProblems(cJSON *problems)//lists all the problems of a contest
{


}

void applyForContest(char *token, int contest_id)// this function is for applying for a contest
{



}



