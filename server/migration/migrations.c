//
// Created by bedilbek on 12/11/17.
//

#include "migrations.h"

const char *migrations[] = {"CREATE SEQUENCE users_id_seq INCREMENT BY 1 MINVALUE 1;",
                            "CREATE SEQUENCE category_id_seq INCREMENT BY 1 MINVALUE 1;",
                            "CREATE SEQUENCE contest_id_seq INCREMENT BY 1 MINVALUE 1;",
                            "CREATE SEQUENCE problem_id_seq INCREMENT BY 1 MINVALUE 1;",
                            "CREATE SEQUENCE problem_result_id_seq INCREMENT BY 1 MINVALUE 1;",
                            "CREATE SEQUENCE test_case_id_seq INCREMENT BY 1 MINVALUE 1;",
                            "CREATE TABLE category\n"
                                    "(\n"
                                    "    id INTEGER DEFAULT nextval('category_id_seq'::regclass) PRIMARY KEY NOT NULL,\n"
                                    "    name VARCHAR(100) NOT NULL,\n"
                                    "    description TEXT,\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL\n"
                                    ");",
                            "CREATE TABLE contest\n"
                                    "(\n"
                                    "    id INTEGER DEFAULT nextval('contest_id_seq'::regclass) PRIMARY KEY NOT NULL,\n"
                                    "    author_id INTEGER NOT NULL,\n"
                                    "    starts_at TIMESTAMP NOT NULL,\n"
                                    "    ends_at TIMESTAMP NOT NULL,\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    description TEXT\n"
                                    ");",
                            "CREATE TABLE contest_problem\n"
                                    "(\n"
                                    "    contest_id INTEGER NOT NULL,\n"
                                    "    problem_id INTEGER NOT NULL,\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    CONSTRAINT contestproblem_pk_problemid_contestid PRIMARY KEY (contest_id, problem_id)\n"
                                    ");",
                            "CREATE TABLE problem\n"
                                    "(\n"
                                    "    id INTEGER DEFAULT nextval('problem_id_seq'::regclass) PRIMARY KEY NOT NULL,\n"
                                    "    category_id INTEGER NOT NULL,\n"
                                    "    description TEXT NOT NULL,\n"
                                    "    input_format TEXT NOT NULL,\n"
                                    "    output_format TEXT NOT NULL,\n"
                                    "    time_limit INTEGER NOT NULL,\n"
                                    "    memory_limit INTEGER NOT NULL,\n"
                                    "    max_points INTEGER DEFAULT 0 NOT NULL,\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP\n"
                                    ");",
                            "CREATE TABLE problem_result\n"
                                    "(\n"
                                    "    id INTEGER DEFAULT nextval('problem_result_id_seq'::regclass) PRIMARY KEY NOT NULL,\n"
                                    "    user_id INTEGER NOT NULL,\n"
                                    "    contest_id INTEGER NOT NULL,\n"
                                    "    problem_id INTEGER NOT NULL,\n"
                                    "    points INTEGER DEFAULT 0 NOT NULL,\n"
                                    "    success BOOLEAN DEFAULT true,\n"
                                    "    failed_test_case_id INTEGER,\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    trial_number INTEGER DEFAULT 0 NOT NULL\n"
                                    ");",
                            "CREATE TABLE test_case\n"
                                    "(\n"
                                    "    id INTEGER DEFAULT nextval('test_case_id_seq'::regclass) PRIMARY KEY NOT NULL,\n"
                                    "    problem_id INTEGER NOT NULL,\n"
                                    "    input_file_name VARCHAR(100) NOT NULL,\n"
                                    "    output_file_name VARCHAR(100) NOT NULL,\n"
                                    "    explanation TEXT,\n"
                                    "    is_sample BOOLEAN DEFAULT true NOT NULL,\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL\n"
                                    ");",
                            "CREATE TABLE user_contest_result\n"
                                    "(\n"
                                    "    user_id INTEGER NOT NULL,\n"
                                    "    contest_id INTEGER NOT NULL,\n"
                                    "    total_points INTEGER DEFAULT 0 NOT NULL,\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    CONSTRAINT user_contest_result_pk_usr_id_cntst_id PRIMARY KEY (user_id, contest_id)\n"
                                    ");",
                            "CREATE TABLE users\n"
                                    "(\n"
                                    "    id INTEGER DEFAULT nextval('users_id_seq'::regclass) PRIMARY KEY NOT NULL,\n"
                                    "    fname VARCHAR(100) NOT NULL,\n"
                                    "    lname VARCHAR(100) DEFAULT NULL::character varying,\n"
                                    "    username VARCHAR(100) NOT NULL,\n"
                                    "    password VARCHAR(100) NOT NULL,\n"
                                    "    email VARCHAR(100),\n"
                                    "    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\n"
                                    "    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL\n"
                                    ");",
                            "CREATE UNIQUE INDEX category_name_uindex ON category (name);",
                            "ALTER TABLE contest ADD FOREIGN KEY (author_id) REFERENCES users (id);",
                            "ALTER TABLE contest_problem ADD FOREIGN KEY (problem_id) REFERENCES problem (id);",
                            "ALTER TABLE problem ADD FOREIGN KEY (category_id) REFERENCES category (id);",
                            "ALTER TABLE problem_result ADD FOREIGN KEY (user_id) REFERENCES users (id);",
                            "ALTER TABLE problem_result ADD FOREIGN KEY (contest_id) REFERENCES contest (id);",
                            "ALTER TABLE problem_result ADD FOREIGN KEY (problem_id) REFERENCES problem (id);",
                            "ALTER TABLE problem_result ADD FOREIGN KEY (failed_test_case_id) REFERENCES test_case (id);",
                            "ALTER TABLE test_case ADD FOREIGN KEY (problem_id) REFERENCES problem (id);",
                            "ALTER TABLE user_contest_result ADD FOREIGN KEY (user_id) REFERENCES users (id);",
                            "ALTER TABLE user_contest_result ADD FOREIGN KEY (contest_id) REFERENCES contest (id);",
                            "CREATE UNIQUE INDEX users_username_uindex ON users (username);",
                            "CREATE UNIQUE INDEX users_email_uindex ON users (email);",
                            "ALTER TABLE users ADD COLUMN token VARCHAR(100) UNIQUE DEFAULT NULL",
                            "ALTER TABLE contest ADD COLUMN title VARCHAR(100) DEFAULT NULL,\n"
                                    "    ADD COLUMN reg_start_time TIMESTAMP,\n"
                                    "    ADD COLUMN reg_end_time TIMESTAMP;",
                            "CREATE SEQUENCE file_id_seq INCREMENT BY 1 MINVALUE 1;",
                            "CREATE TABLE file (\n"
                                    "    id INTEGER PRIMARY KEY DEFAULT nextval('file_id_seq'::regclass),\n"
                                    "    user_id INTEGER NULL,\n"
                                    "    path VARCHAR(200) NULL,\n"
                                    "    CONSTRAINT file_fk_user_id FOREIGN KEY (user_id) REFERENCES users(id)\n"
                                    ");",
                            "ALTER TABLE problem\n"
                                    "    RENAME COLUMN input_format TO input_file_id;",
                            "ALTER TABLE problem\n"
                                    "    RENAME COLUMN output_format to output_file_id;",
                            "ALTER TABLE test_case\n"
                                    "    RENAME COLUMN output_file_name to output_file_id;",
                            "ALTER TABLE test_case\n"
                                    "    RENAME COLUMN input_file_name to input_file_id;",
                            "ALTER TABLE problem\n"
                                    "ALTER input_file_id SET DATA TYPE INTEGER USING input_file_id::INTEGER;",
                            "ALTER TABLE problem\n"
                                    "ALTER output_file_id SET DATA TYPE INTEGER USING output_file_id::INTEGER;",
                            "ALTER TABLE test_case\n"
                                    "ALTER input_file_id SET DATA TYPE INTEGER USING input_file_id::INTEGER;",
                            "ALTER TABLE test_case\n"
                                    "ALTER output_file_id SET DATA TYPE INTEGER USING output_file_id::INTEGER;",
                            "ALTER TABLE file\n"
                                    "    ADD COLUMN extension VARCHAR(10) CHECK (extension in ('.txt', '.c'));",
                            NULL
};
/** TODO
 * contest-fields: title, reg_start_time, reg_end_time **/
int run_migrations(struct Database *db) {
    int created = 1;
    if (!exist_migration_table(db))
        created = create_migration_table(db);
    if (!created)
        return 0;
    int count = count_migrations(db);

    if (!migrations_runnable(count))
        return 0;

    return migrate(db);
}

int count_migrations(struct Database *db) {
    cJSON *msg = select_query(db, "SELECT count(id) \n"
            "FROM migration");

    if ((int) cJSON_parser(cJSON_GetObjectItem(msg, "status")) != DATABASE_TUPLES_OK)
        return -1;

    return strtol(cJSON_parser(cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(msg, "data"), 0), "count")),
                  NULL, 10);
}

int migrations_runnable(int count_migrations) {
    if (count_migrations < 0 || (count_migrations > 0 && migrations[count_migrations] == NULL))
        return 0;
    return 1;
}

int migrate(struct Database *db) {
    int i = count_migrations(db) - 1;
    cJSON *msg = cJSON_CreateObject();

    while (migrations[++i] != NULL) {
        msg = select_query(db, migrations[i]);
        fprintf(stdout, "Migration number-%d: %s ->", i, migrations[i]);
        if ((int) cJSON_parser(cJSON_GetObjectItem(msg, "status")) != DATABASE_NO_TUPLES_OK) {
            fprintf(stderr, "failed: %s\n", PQerrorMessage(db->pgConn));
            break;
        }
        cJSON_Delete(msg);
        char insert_sql[100];
        sprintf(insert_sql, "INSERT INTO migration VALUES(DEFAULT, \'Migration-%d\', DEFAULT)", i);
        msg = insert_query(db, insert_sql);
        if ((int) cJSON_parser(cJSON_GetObjectItem(msg, "status")) != DATABASE_NO_TUPLES_OK) {
            fprintf(stderr, "Insert migration number-%d failed: %s", i, PQerrorMessage(db->pgConn));
            break;
        }
        fprintf(stdout, "succeeded\n");
    }
    cJSON_Delete(msg);
    return i;
}

int exist_migration_table(struct Database *db) {
    cJSON *msg = select_query(db, "SELECT to_regclass(\'migration\')");

    if ((int) cJSON_parser(cJSON_GetObjectItem(msg, "status")) != DATABASE_TUPLES_OK) {
        fprintf(stderr, "Check migration table existence query failed: %s", PQerrorMessage(db->pgConn));
        return -1;
    }

    if (strcmp((char *) cJSON_parser(
            cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(msg, "data"), 0), "to_regclass")),
               "migration") != 0)
        return 0;

    return 1;
}

int create_migration_table(struct Database *db) {
    cJSON *msg = select_query(db, "CREATE SEQUENCE migration_id_seq INCREMENT BY 1 MINVALUE 1");

    if ((int) cJSON_parser(cJSON_GetObjectItem(msg, "status")) != DATABASE_NO_TUPLES_OK) {
        fprintf(stderr, "Creation of migration sequence query failed: %s", PQerrorMessage(db->pgConn));
        return 0;
    }
    cJSON_Delete(msg);

    msg = select_query(db, "CREATE TABLE migration\n"
            "(\n"
            "id INTEGER DEFAULT nextval('migration_id_seq'::regclass) PRIMARY KEY NOT NULL,\n"
            "NAME VARCHAR(100) NOT NULL,\n"
            "created_at TIMESTAMP DEFAULT current_timestamp\n"
            ");");

    if ((int) cJSON_parser(cJSON_GetObjectItem(msg, "status")) != DATABASE_NO_TUPLES_OK) {
        fprintf(stderr, "Creation of migration table query failed: %s", PQerrorMessage(db->pgConn));
        return 0;
    }

    return 1;
}