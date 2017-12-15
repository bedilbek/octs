////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "client.h"
#include "ui.c"

void print_table_TEST()
{
    char *id = "Contest_ID";
    char *title = "Title";
    char *starts_at = "Starts_at";
    char *ends_at = "Ends_at";
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s|%-35s|%-15s|\n", id, title, starts_at, ends_at, "reg_end_date");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    int i;
    for(i=0;i<5;i++) {
        printf("   %-9d|", (i+3)*1232);
        printf("%-35s|", "Quadratic equation");
        printf("%-15s|", "45-45-1997 12:30");
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------------------------------\n");
    }

}

int main() {
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

        getProblemFromUser();



    return 0;
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
