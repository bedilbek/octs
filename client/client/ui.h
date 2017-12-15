//
// Created by shakhobiddin on 12/13/17.
//

#ifndef OS_PROJECT_UI_H
#define OS_PROJECT_UI_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<cJSON.h>


//cJSON *loginMenu();


void saveToFileOcts(char *token);

cJSON *loginMenu();

int isLoggedIn();

void logoutFunction();

char *getToken();

void showContests(cJSON *contests, int size);

void showContestProblems(cJSON *problems, int size);

cJSON *registerMenu();

#endif //OS_PROJECT_UI_H

