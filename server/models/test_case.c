//
// Created by bedilbek on 12/10/17.
//

#include "test_case.h"

#define TEST_CASE_CLONE 2

#define TEST_CASE_ID "id"
#define TEST_CASE_PROBLEM_ID "problem_id"
#define TEST_CASE_INPUT_FILE_ID "input_file_path"
#define TEST_CASE_OUTPUT_FILE_ID "output_file_path"
#define TEST_CASE_EXPLANATION "explanation"
#define TEST_CASE_IS_SAMPLE "is_sample"
#define TEST_CASE_CREATED_AT "created_at"
#define TEST_CASE_UPDATED_AT "updated_at"

cJSON *create_test_case_char(int problem_id, int input_file_id, int output_file_id,
                             char *explanation, int is_sample) {
    struct Database *db = new(Database);

    char insert_sql[1024];
    char param[1024];
    sprintf(param, "%d", is_sample);
    char *param_values[] = {param};
    sprintf(insert_sql, "INSERT INTO test_case \n"
                    "VALUES (DEFAULT, %d, %d, %d, \'%s\', $1, DEFAULT, DEFAULT) \n"
                    "RETURNING id",
            problem_id, input_file_id, output_file_id,
            explanation);

    cJSON *msg = insert_query_params(db, insert_sql, 1, param_values);
    delete(db);

    return msg;
}

cJSON *create_test_case_cJSON(cJSON *data) {
    return create_test_case_char(
            (cJSON_GetObjectItem(data, TEST_CASE_PROBLEM_ID))->valueint,
            (cJSON_GetObjectItem(data, TEST_CASE_INPUT_FILE_ID))->valueint,
            (cJSON_GetObjectItem(data, TEST_CASE_OUTPUT_FILE_ID))->valueint,
            (cJSON_GetObjectItem(data, TEST_CASE_EXPLANATION))->valuestring,
            (cJSON_GetObjectItem(data, TEST_CASE_IS_SAMPLE))->valueint);
}

cJSON *get_test_cases_of_problem(int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM test_case \n"
                    "where problem_id=%d",
            problem_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_sample_test_cases_of_problem(int problem_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM test_case \n"
                    "where problem_id=%d \n"
                    "AND is_sample=1",
            problem_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

cJSON *get_test_case_by_id(int test_case_id) {
    struct Database *db = new(Database);
    char select_sql[1024];

    sprintf(select_sql,
            "SELECT * FROM test_case \n"
                    "where id=%d",
            test_case_id);

    cJSON *msg = select_query(db, select_sql);
    delete(db);
    return msg;
}

static void *test_case_ctor(void *_self, va_list *arguments) {
    struct TestCase *self = _self;

    const cJSON *data = va_arg(*arguments, const cJSON *);
    if (data)
        self->data = data;
    else {
        self->data = cJSON_CreateObject();
        return self;
    }
    assert(self->data);
    const int tst_cs_args = va_arg(*arguments, const int);
    if (tst_cs_args == TEST_CASE_CLONE)
        return self;

    cJSON *create_tst_cs_msg = create_test_case_cJSON(self->data);

    if ((cJSON_GetObjectItem(create_tst_cs_msg, "status"))->valueint != DATABASE_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(create_tst_cs_msg, "message"))->valuestring);
        delete(self);
        return NULL;
    }

    int test_case_id = cJSON_parser(
            cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(create_tst_cs_msg, "data"), 0), "id"));

    cJSON_AddNumberToObject(self->data, "id", test_case_id);

    return self;
}

static void *test_case_clone(const void *_self) {
    const struct TestCase *self = _self;
    struct TestCase *new_test_case = new(TestCase, self->data, TEST_CASE_CLONE);
    return new_test_case;
}

static void test_case_set(struct TestCase *_self, char *field, void *value) {
    assert(_self && _self->data);
    if (cJSON_GetObjectItem(_self->data, field) != cJSON_NULL)
        cJSON_DeleteItemFromObject(_self->data, field);
    int test_case_id = (cJSON_GetObjectItem(_self->data, TEST_CASE_ID))->valueint;
    assert(test_case_id);

    struct Database *db = new(Database);
    char update_sql[1024];
    char *values[] = {value};

    //update user in db;
    sprintf(update_sql, "UPDATE test_case SET %s=$1 WHERE id=%d", field, test_case_id);
    cJSON *msg = update_query_params(db, update_sql, 1, values);
    delete(db);
    if ((cJSON_GetObjectItem(msg, "status"))->valueint != DATABASE_NO_TUPLES_OK) {
        fprintf(stderr, "%s", (cJSON_GetObjectItem(msg, "message"))->valuestring);
        return;
    }
    cJSON_AddStringToObject(_self->data, field, value);
}

static void *test_case_get(struct TestCase *_self, char *field, void *value) {
    assert(_self && _self->data);
    return cJSON_parser(cJSON_GetObjectItem(_self->data, field));
}

static int test_case_differ(const void *_self, const void *_b) {
    const struct TestCase *self = _self;
    const struct TestCase *b = _b;
    if (self == b)
        return 0;
    if (!b || b->class != TestCase)
        return 1;
    return cJSON_Compare(self->data, b->data, 1);
}

static char *test_case_toJson(struct TestCase *_self) {
    assert(_self && _self->data);
    return cJSON_Print(_self->data);
}

static void *test_case_dtor(void *_self) {
    struct TestCase *self = _self;
    cJSON_Delete(self->data);
    return self;
}

static const struct Class _TestCase = {
        sizeof(struct TestCase),
        test_case_ctor,
        test_case_dtor,
        test_case_clone,
        test_case_differ,
        test_case_set,
        test_case_get,
        test_case_toJson
};

const void *TestCase = &_TestCase;

//maps cJSON to TestCase struct and returns number of elements.
//to must be passed by reference
int map_test_case(cJSON *from, struct TestCase **to)
{
    int status = (int) cJSON_parser(cJSON_GetObjectItem(from, "status"));

    if (status == DATABASE_TUPLES_OK)
    {
        const int count = (int) cJSON_parser(cJSON_GetObjectItem(from, "count"));
        struct TestCase *testcases = malloc(sizeof(struct TestCase) * count);
        int i = 0;
        cJSON *data;
        for(i = 0; i < count; i++)
        {
            data = cJSON_GetArrayItem(cJSON_GetObjectItem(from, "data"), i);
            testcases[i].problem_id = (int) cJSON_parser(cJSON_GetObjectItem(data, TEST_CASE_PROBLEM_ID));
            testcases[i].id = (int) cJSON_parser(cJSON_GetObjectItem(data, TEST_CASE_ID));
            testcases[i].explanation = (char*) cJSON_parser(cJSON_GetObjectItem(data, TEST_CASE_EXPLANATION));
            testcases[i].is_sample = (bool) cJSON_parser(cJSON_GetObjectItem(data, TEST_CASE_IS_SAMPLE));

            int input_file_id = (int) cJSON_parser(cJSON_GetObjectItem(data, TEST_CASE_INPUT_FILE_ID));
            int output_file_id  = (int) cJSON_parser(cJSON_GetObjectItem(data, TEST_CASE_OUTPUT_FILE_ID));

            testcases[i].input_file_path = get_file_path(input_file_id);
            testcases[i].output_file_path = get_file_path(output_file_id);

            if (testcases[i].input_file_path == NULL || testcases[i].output_file_path == NULL)
                return  -1;
        }
        *to = testcases;
        return count;
    }
    else
    {
        return  -1;
    }
}