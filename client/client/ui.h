//
// Created by shakhobiddin on 12/13/17.
//

#ifndef OS_PROJECT_UI_H
#define OS_PROJECT_UI_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<cJSON.h>

#define TEST_CASE_OK 800
#define COMPILATION_ERROR 801
#define TEST_CASE_FAILED 802
#define TEST_CASES_SUCCESS 803
#define TEST_CASES_UNDEFINED_ERROR 804
#define TEST_CASE_TIME_LIMIT 805


void saveToFileOcts(char *token);

cJSON *loginMenu();

int isLoggedIn();

void logoutFunction();

char *getToken();

void showContests(cJSON *contests, int size);

cJSON *signup();

void show_problems(cJSON *problems);

cJSON *getProblemFromUser();

void show_contest(cJSON *contest);

void show_problem(cJSON *problem);

void show_results(cJSON *results);

cJSON *get_files();

#endif //OS_PROJECT_UI_H

