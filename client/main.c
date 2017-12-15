////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "client.h"
cJSON *loginMenu()
{

}

void logoutFunction() // this function deletes the file with the token
{

}

char *getToken()
{

}
int main(int argc, char *argv[]){
    struct Client *client = new(Client, SERVER_LISTEN_PORT);
    struct Client *file_client= new(Client, FILE_SERVER_LISTEN_PORT);

    if(argc==2 && (strcmp(argv[1],"login")==0 || strcmp(argv[1],"Login")==0)) // OCTS Login
    {
        cJSON *responseLogin;
        cJSON *loginDetails;

        if(!isLoggedIn()) // isLoggedIn function checks whether there is a file with token
        {
            int status;
            loginDetails = loginMenu(); // call Login menu function (username , password)

            responseLogin = (cJSON *) send_message(client, 0, loginDetails);
            status = cJSON_GetObjectItem(responseLogin, "status")->valueint;
            if (status == 200 || status == 201)
            {
//            char* answer = cJSON_GetObjectItem(responseLogin, "fname")->valuestring;  // first name of user
//            char* answer2 = cJSON_GetObjectItem(responseLogin,"lname")->valuestring; // last name of user
                char *token = cJSON_GetObjectItem(responseLogin, "token")->valuestring; // token of user
//          char* id_user = cJSON_GetObjectItem(responseLogin,"id")->valuestring; // user id

                saveToFileOcts(token); // save name lastname and token with id in .octs
                printf("Successfully Logged In");
            } else
            {
                char *error = cJSON_GetObjectItem(responseLogin,"err_msg")->valuestring;
                printf(error);
            }
        }
        else
        {
            printf("You have already signed in!\n");
        }
    }
    else if (argc==2 && strcmp(argv[1],"logout")==0) // OCTS logout
    {
        if(isLoggedIn())
        {
            logoutFunction(); // logout function just deletes the file with the token of the current user
            printf("You logged out successfully \n"); // print to user that he/she logged out
        }
        else
        {
            printf("You haven't logged in yet!\n");
        }
    }
    else if (argc==2 && (strcmp(argv[1],"contests")==0 || strcmp(argv[1],"-c")==0)) // OCTS see all contest of user
    {
        if(isLoggedIn())
        {
            char* token = getToken();  // this function return userID from file .octs
            cJSON *tokenJSON = cJSON_CreateObject();
            cJSON_AddStringToObject(tokenJSON,"token",token);
            cJSON *response;
            response = (cJSON *) send_message(client, 3 , tokenJSON);
            int status = cJSON_GetObjectItem(response,"status")->valueint;
            int size = cJSON_GetArraySize(cJSON_GetObjectItem(response,"data"));
            //cJSON *obj = cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(response, "data"), 0), "id");
            showContests(cJSON_GetObjectItem(response, "data"),size);
        }
        else
        {
            printf("You haven't logged in yet\n");
        }

    }
    else if(argc == 4 && strcmp(argv[1],"ls")==0 && (strcmp(argv[2],"contest")==0 || strcmp(argv[2],"-c")==0))
    {
        if(isLoggedIn())
        {
            /*
         * 1. login is checked
         * 2. then it is check whether the user is in the contest
         * 3. problems list is received from server
         * 4. here the showContestProblems(cjson) function will display problems
        */
            char *contest_id;
            char* token = getToken();
            strcpy(contest_id,argv[3]);
            cJSON *contest = cJSON_CreateObject();
            cJSON_AddStringToObject(contest,"contest_id",contest_id);
            cJSON_AddStringToObject(contest,"token",token);

            cJSON *response;
            response = (cJSON *) send_message(client, 4 , contest);


            int status = cJSON_GetObjectItem(response,"err_msg")->valueint;
            if(status == 200 || status == 201)
            {

                int size = cJSON_GetArraySize(cJSON_GetObjectItem(response,"data"));
                showContestProblems(cJSON_GetObjectItem(response, "data"), size);
            }
            else
            {
                printf("Please enter valid contest id\n");
            }
        }
        else
        {
            printf("You haven't logged in yet\n");
        }



    }
    else if(argc == 3 && strcmp(argv[1],"submit")==0)
    {
        char *PATH = argv[2];
        int problem_id=argv[3];
        char *token = getToken();
        if(isLoggedIn())
        {

            cJSON *response = send_file(file_client, token , PATH );
            int status, file_id;
            if(!(status=get_attr(response, "status", INTEGER))==200){
                printf(get_attr(response, "err_msg", STRING));
                return -1;
            }
            file_id=get_attr(response, "file_id", INTEGER);
            cJSON * request = cJSON_CreateObject();
            cJSON_AddNumberToObject(request, "problem_id", problem_id);
            cJSON_AddNumberToObject(request, "file_id", file_id);
            response = send_message(client, token, NUMBER/*Number of method*/, request);
            if((status=get_attr(response, "status", INTEGER))==201){
                printf("Solution is successfully submitted");
            }else{
                printf(get_attr(response, "err_msg", STRING));
            }
        }


    }
    else if(argc == 2 && strcmp(argv[1],"register"))
    {
        registerMenu();
    }
    else if(argc == 3 && strcmp(argv[1],"apply"))
    {
        int contest_id = argv[2];
        char *token;
        if(isLoggedIn())
        {
            token = getToken();
            cJSON *apply = cJSON_CreateObject();
            cJSON_AddStringToObject(apply,"token",token);
            cJSON_AddNumberToObject(apply,"contest_id",contest_id);
            cJSON *response;
            response = (cJSON *) send_message(client, 4 , apply);
            int status = cJSON_GetObjectItem("status",response);
            if(status == 200 || status == 201)
            {

                char *message = cJSON_GetObjectItem("message",response);
                printf(message);
            } else
            {
                char *err_msg = cJSON_GetObjectItem("err_msg",response);
                printf(err_msg);
            }
        }
        else
        {
            printf("You haven't logged in\n");
        }



    }
    else if(argc == 4 && strcmp(argv[1],"ls") && strcmp(argv[2],"problem"))
    {
        int problem_id = argv[3];
        /*
         * 1. login is checked
         * 2. problems description is received from server
         * 3. here some function will display description
        */
        if(isLoggedIn())
        {
            char *token = getToken();
            cJSON *problem = cJSON_CreateObject();
            cJSON_AddStringToObject(problem,"token",token);
            cJSON_AddStringToObject(problem,"problem_id",problem_id);
            cJSON *response;
            response = (cJSON *) send_message(client, 4 , problem);

            int status = cJSON_GetObjectItem(response,"status")->valueint;
            if(status == 200)
            {

                cJSON *problemDetails = cJSON_GetObjectItem(response,"data");
                showProblemetails(problemDetails);
            }
            else
            {
                char *message = cJSON_GetObjectItem(response,"err_msg")->valuestring;
                printf(message);
            }

        }
        else
        {
            printf("You haven't logged in yet");
        }
    }
    else if(argc == 3 && strcmp(argv[1],"create") && (strcmp(argv[2],"problem") || strcmp(argv[2],"-p")))
    {
        cJSON *newProblem;

        if(isLoggedIn())
        {
            char *token = getToken();
            newProblem = getProblemFromUser(); /*this function returns the new problem's cJSON object*/
            char *path1 = cJSON_GetObjectItem(newProblem, "absolute_path1")->valuestring;
            char *path2 = cJSON_GetObjectItem(newProblem, "absolute_path2")->valuestring;
            int file1_id, file2_id;
            int stat;
            cJSON *response;
            cJSON *responseForFile1 = send_file(file_client, token, path);
            cJSON *responseForFile2 = send_file(file_client, token, path);

            if(!(status=get_attr(response, "status", INTEGER))==200)
            {
                printf(get_attr(response, "err_msg", STRING));
            }
            else
            {

                file1_id = get_attr(responseForFile1, "file_id", INTEGER);
                file2_id = get_attr(responseForFile2, "file_id", INTEGER);
                cJSON_AddNumberToObject(newProblem, "input_file_id", file1_id);
                cJSON_AddNumberToObject(newProblem, "output_file_id", file2_id);

                response = send_message(client, CREATE_PROBLEM/*method number*/, newProblem);
                stat = cJSON_GetObjectItem(response, "status");
                if(stat==200 || stat==201)
                {
                    printf(cJSON_GetObjectItem(response, "message"));
                    printf("The problem has successfully created\n");
                }
                else
                {
                    printf(cJSON_GetObjectItem(response, "err_msg"));
                }
            }
        }
        else
        {
            printf("You haven't logged in!");
        }
    }
    else if(argc == 3 && strcmp(argv[1],"create") && (strcmp(argv[2],"contest") || strcmp(argv[2],"-c")))
    {



    }



}