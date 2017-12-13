//#include "lib.h"
//#include "model.h"
//#include "server.h"
//#include "migration/migrations.h"
//
//int main() {
//
//    struct Database *db = new(Database);
//
//    run_migrations(db);
//
//    //struct String *a = new(String, "text A");
//    //printf("%s", toJson(a));
//    //struct String *b = clone(a);
//
//    //struct Dict *keyPair = new(Dict, "info", "man");
//    //set(keyPair->data, "info", "as");
//    //set(keyPair, "info", "as");
//    //printf("hello %s", toJson(keyPair));
//
////    void* b = new(String, "text B");
////
////    if (!differ(a, aa))
////        printf("yeees\n");
////    printf("%s\n", a->text);
////    printf("%s => %s\n", keyPair->key, keyPair->value);
////    struct Database *db = new(Database);
////    cJSON *dbData = select_query(db, "SELECT * FROM users");
////    printf(cJSON_Print(dbData));
////    delete(db);
////    //delete(a),
////    //delete(b), delete(keyPair);
//    setbuf(stdout, NULL);
//
//    //creating a user
//
//    cJSON *usrJSON = cJSON_Parse("{\"fname\":\"tom\","
//                                         "\"lname\":\"isaak\","
//                                         "\"username\":\"ttom\","
//                                         "\"password\":\"tom\","
//                                         "\"email\":\"ttom@gmail.com\"}");
//    struct User *usr = new(User, usrJSON);
//    printf("%s\n", toJson(usr));
//    set(usr, "fname", "bediko");
//    printf("%s\n", get(usr, "fname"));
//    printf("%s\n", get(usr, "username"));
//    printf("%d\n", get(usr, "id"));
//    delete(usr);
//
//    //creating a category
//    cJSON *ctgryJSON = cJSON_Parse("{\"name\":\"Awesome category\","
//                                           "\"description\":\"Very good category\"}");
//    struct Category *ctgry = new(Category, ctgryJSON);
//    printf("%s\n", toJson(ctgry));
//    set(ctgry, "description", "Very Bad category");
//    printf("%s\n", get(ctgry, "description"));
//    printf("%s\n", get(ctgry, "name"));
//    printf("%d\n", get(ctgry, "id"));
//    delete(ctgry);
//
//    //creating a problem
//    cJSON *problemJSON = cJSON_Parse("{\"category_id\":2,"
//                                             "\"description\":\"Very good problem\","
//                                             "\"input_format\":\"this kind of input format\","
//                                             "\"output_format\":\"this kind of output format\","
//                                             "\"time_limit\": 2, "
//                                             "\"memory_limit\": 256,"
//                                             "\"max_points\": 5}");
//
//    struct Problem *problem = new(Problem, problemJSON);
//    printf("%s\n", toJson(problem));
//    set(problem, "description", "Very Bad problem");
//    printf("%s\n", get(problem, "description"));
//    printf("%s\n", get(problem, "output_format"));
//    printf("%d\n", get(problem, "id"));
//    printf("%d\n", get(problem, "memory_limit"));
//    delete(problem);
//
//    //creating a test_case
//    cJSON *test_caseJSON = cJSON_Parse("{ \"problem_id\":2,"
//                                               "\"input_file_name\":\"Very good input file name\","
//                                               "\"output_file_name\":\"Very good output file name\","
//                                               "\"explanation\":\"this is good test_case explanation\","
//                                               "\"is_sample\": 1 }");
//
//    struct TestCase *test_case = new(TestCase, test_caseJSON);
//    printf("%s\n", toJson(test_case));
//    set(test_case, "explanation", "this is bad test_case explanation");
//    printf("%s\n", get(test_case, "explanation"));
//    printf("%s\n", get(test_case, "output_file_name"));
//    printf("%d\n", get(test_case, "is_sample"));
//    printf("%d\n", get(test_case, "id"));
//    delete(test_case);
//
//    //creating a contest
//    cJSON *contestJSON = cJSON_Parse("{ \"author_id\":2,"
//                                             "\"starts_at\":\"10.12.2017 22:51:00\","
//                                             "\"ends_at\":\"10.12.2017 23:51:00\","
//                                             "\"description\":\"Very good description\"}");
//
//    struct Contest *contest = new(Contest, contestJSON);
//    printf("%s\n", toJson(contest));
//    set(contest, "description", "Very bad description");
//    printf("%s\n", get(contest, "description"));
//    printf("%s\n", get(contest, "starts_at"));
//    printf("%d\n", get(contest, "author_id"));
//    printf("%d\n", get(contest, "id"));
//    delete(contest);
//
//    //creating a contest_problem
//    cJSON *contest_problemJSON = cJSON_Parse("{ \"contest_id\":1,"
//                                                     "\"problem_id\":3}");
//
//    struct ContestProblem *contest_problem = new(ContestProblem, contest_problemJSON);
//    printf("%s\n", toJson(contest_problem));
//    printf("%d\n", get(contest_problem, "contest_id"));
//    printf("%d\n", get(contest_problem, "problem_id"));
//    delete(contest_problem);
//
//
//    //creating a problem_result
//    cJSON *problem_resultJSON = cJSON_Parse("{ \"user_id\":1,"
//                                                    "\"problem_id\":4,"
//                                                    "\"contest_id\":3,"
//                                                    "\"points\":1,"
//                                                    "\"success\":1,"
//                                                    "\"failed_test_case_id\": 0}");
//
//    struct ProblemResult *problem_result = new(ProblemResult, problem_resultJSON);
//    printf("%s\n", toJson(problem_result));
//    printf("%d\n", get(problem_result, "contest_id"));
//    printf("%d\n", get(problem_result, "problem_id"));
//    delete(problem_result);
//
//    //creating a problem_result
//    cJSON *user_contest_resultJSON = cJSON_Parse("{ \"user_id\":1,"
//                                                         "\"contest_id\":4,"
//                                                         "\"total_points\":1}");
//
//    struct UserContestResult *user_contest_result = new(UserContestResult, user_contest_resultJSON);
//    printf("%s\n", toJson(user_contest_result));
//    printf("%d\n", get(user_contest_result, "contest_id"));
//    printf("%d\n", get(user_contest_result, "user_id"));
//    delete(user_contest_result);
//
////    server_listen(new(Server));
//}

////
//// Created by Tolqinbek Isoqov on 12/3/17.
////

#include "lib.h"
#include <pthread.h>
#include "server.h"

//
int main() {
//    setbuf(stdout, NULL);
    pthread_t server_pid, file_server_pid;
    struct Server *server = new(Server, SERVER_LISTEN_PORT);
//    struct Server *file_server = new(Server, FILE_SERVER_LISTEN_PORT);
//    pthread_create(&file_server_pid, NULL, file_server_listen, file_server);
    pthread_create(&server_pid, NULL, server_listen, server);
//    server_listen(server);
    pthread_join(server_pid, NULL);
//    pthread_join(file_server_pid, NULL);
}