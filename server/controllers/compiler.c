//
// Created by Sherzod on 12/14/17.
//

#include "compiler.h"

int temp_file_name = 0;
int temp_is_locked = 0;

int compare_outputs(FILE *actual, FILE *expected) {
    char a_buff;
    char e_buff;

    while (1) {
        a_buff = fgetc(actual);
        e_buff = fgetc(expected);
        if (a_buff != e_buff) {
            return 0;
        }

        if (a_buff == EOF && e_buff == EOF) {
            return 1;
        }

        if (a_buff == EOF || e_buff == EOF) {
            return 0;
        }
    }
}

char *get_temp_file_name() {
    int test = temp_file_name;
    while (1) {
        if (temp_is_locked == 0) {
            temp_is_locked = 1;
            char temp[1000000];
            sprintf(temp, "%d\0", ++temp_file_name);
            temp_is_locked = 0;
            return temp;
        }
    }
}

char *get_temp_location() {
    char path[1024] = TEMP_FILE_STORAGE;
    strcat(path, "temp/");
    return path;
}

//1 if error otherwise 0
int if_error(char *error_file) {
    FILE *file = fopen(error_file, "r+");
    char buff;
    int i = 0;
    for (i = 0; 1; i++) {
        buff = fgetc(file);
        if (buff == EOF && i <= 1) {

            return 0;
        } else {
            return 1;
        }
    }
}

//if compilation was failed, report it to user
void report_compilation_error(char *error_file) {
    FILE *error = fopen(error_file, "r");
    int count = 0;
    char buff;
    char str_buffer[100000];
    while (1) {
        buff = fgetc(error);
        str_buffer[count] = buff;
        count++;
        if (buff == EOF) {
            fclose(error);
            break;
        }
    }

    char *msg = malloc((count + 1) * sizeof(char));
    int i = 0;
    for (i = 0; i < count; i++)
        msg[i] = str_buffer[i];
    msg[count] = '\0';
    cJSON *report = cJSON_CreateObject();
    cJSON_AddNumberToObject(report, "status", COMPILATION_ERROR);
    cJSON_AddStringToObject(report, "message", msg);

}

//execute code with given test case
int execute(char *code_path, struct TestCase testCase, int time_limit) {
    time_t start, end;
    double cpu_time_used;

    int status; //execution status
    char command[100000];   //gcc command buffer
    char *temp_location = get_temp_location();  //temporary location
    char *temp_file_name = get_temp_file_name(); //temporary file name for code
    char *input_file = testCase.input_file_path; //test case input file location
    char *output_file = testCase.output_file_path; //test case output file location
    char error_file_path[100000] = {}; //error log temporary location
    char code_object[100000] = {}; //compiled code object temporary location
    char code_output[100000] = {}; //code object execution output location

    //prepare command and paths
    strcat(error_file_path, temp_location);
    strcat(error_file_path, temp_file_name);
    strcat(error_file_path, "_error");
    strcat(code_object, temp_location);
    strcat(code_object, temp_file_name);
    strcat(code_object, ".o");
    strcat(code_output, temp_location);
    strcat(code_output, temp_file_name);
    strcat(code_output, "_out");

    sprintf(command, "gcc -o %s %s 2>%s && %s< %s >%s", code_object, code_path, error_file_path, code_object,
            input_file, code_output);



    //int cl = CLOCKS_PER_SEC;
    start = time(NULL); // start execution
    system(command); // execute shell script
    end = time(NULL); // end execution

    cpu_time_used = ((double) (end - start)); // time taken to execute

    if (cpu_time_used > time_limit) {
        status = TEST_CASE_TIME_LIMIT;
    } else
        //check for error
    if (if_error(error_file_path) == 0) {
        FILE *actual_output = fopen(code_output, "r");
        FILE *expected_output = fopen(output_file, "r");
        int result = compare_outputs(actual_output, expected_output); // compares with test case output

        //closes files
        fflush(expected_output);
        fflush(actual_output);
        fclose(expected_output);
        fclose(actual_output);

        if (result == 1) {
            status = TEST_CASE_OK;
        } else {
            status = TEST_CASE_FAILED;
        }
    } else {
        status = COMPILATION_ERROR;
    }

    //removes temporary files
    remove(error_file_path);
    remove(code_output);
    remove(code_object);
    return status;
}


void compile(char *code_path, int user_id, int contest_id, int problem_id) {
    cJSON *test_cases_json = get_test_cases_of_problem(problem_id);
    struct TestCase *test_cases;

    int count = map_test_case(test_cases_json, &test_cases);
    struct Problem *problem = map_problem(get_problem_by_id(problem_id));
    int status = TEST_CASES_UNDEFINED_ERROR;
    int test_case_fail_id = 0;
    int points = 0;
    int i = 0;


    for (i; i < count; i++) {
        status = execute(code_path, test_cases[i], problem->time_limit);
        if (status == TEST_CASE_FAILED || status == TEST_CASE_TIME_LIMIT) {
            test_case_fail_id = test_cases[i].id;
            points = 0;
            break;
        } else if (status == TEST_CASE_OK) {
            points = problem->max_point;
            test_case_fail_id = 0;
            status = TEST_CASES_SUCCESS;
            continue;
        } else if (status == COMPILATION_ERROR) {
            test_case_fail_id = 0;
            points = 0;
            break;
        }
    }
    /**
     * TODO implement point calculation
     * **/

    if (status == TEST_CASES_UNDEFINED_ERROR)
        fprintf(stderr, "Test case map failed");

    cJSON *response = create_problem_result_char(user_id, contest_id, problem_id, points, status, test_case_fail_id);
}