////
//// Created by Tolqinbek Isoqov on 12/3/17.
////
#include "server.h"
#include "migrations.h"
#include "lib.h"
#include "model.h"

int main() {
    struct Database *db = new(Database);
    run_migrations(db);

    pthread_t server_pid, file_server_pid;
    //run_migrations()
//    printf(cJSON_Print(create_file_char(1, "/hello/ok/")));

    struct Server *server = new(Server, SERVER_LISTEN_PORT);
    struct Server *file_server = new(Server, FILE_SERVER_LISTEN_PORT);
    pthread_create(&file_server_pid, NULL, file_server_listen, file_server);
//    pthread_create(&server_pid, NULL, server_listen, server);
//    pthread_join(server_pid, NULL);
    pthread_join(file_server_pid, NULL);
//    char *token;
//    token = generate_token();
//    printf(token);
    //cJSON *response = create_category_char("test_category","test description");
    //int id =  (int) cJSON_parser(cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(response, "data"), 0), "id"));
    //printf(id);
    //create_problem_char(1, "test categry", "test_format", "test_outpu_format", 3, 256, 1000);
    //create_test_case_char(1,"test","test2","test exp", 1);
    //create_problem_result_char(1,1,1,10,1, NULL);
    //struct ProblemResult res;
    //printf(cJSON_Print(get_test_cases_of_problem(1)));

    struct TestCase test;
    test.input_file = "/Users/sherzod/Documents/test_input";
    test.output_file = "/Users/sherzod/Documents/test_output";
    char *code_path = "/Users/sherzod/Documents/test.c";
    //int i = execute(code_path, test);
    //printf("\n\nstatus: %d ", i);

    compile(code_path,1,1,1);
    return  0;
}


