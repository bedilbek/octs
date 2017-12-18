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

cJSON *signup();

void show_contest_problems(cJSON *problem, int size);

cJSON *getProblemFromUser();

void show_contest(cJSON *contest);

void show_problem(cJSON *problem);

#endif //OS_PROJECT_UI_H

