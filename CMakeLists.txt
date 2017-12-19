cmake_minimum_required(VERSION 3.8)
project(os_project)

set(CMAKE_C_STANDARD 11)

set(SERVER_SOURCE_FILES server/message_main.c)
set(FILE_SERVER_SOURCE_FILES server/file_main.c)
set(CLIENT_SOURCE_FILES client/main.c)

include_directories(
        lib
        server/models
        vendor/cJSON
        config
        server/server
        client/client
        server/controllers
        server/migration
        client/controllers
)

include_directories(vendor)

include(server/pgsqlFind.cmake)

add_library(
        lib
        lib/helpers.c
        lib/dictionary.c
        lib/_string.c
)
add_library(
        db
        lib/DataBase.c
        server/db/migration/migrations.c
)
add_library(
        vendor
        vendor/cJSON/cJSON.c
)
add_library(
        model
        server/models/user.c
        server/models/problem.c
        server/models/category.c
        server/models/contest.c
        server/models/contest_problem.c
        server/models/problem_result.c
        server/models/test_case.c
        server/models/user_contest_result.c
        server/models/file.c
)
add_library(
        server
        server/server/server.c
        server/server/message_server.c
        server/server/file_server.c
        server/controllers/compiler.c
)
add_library(
        client
        client/client/client.c
        client/client/send_message.c
        client/client/send_file.c
)

add_library(
        controllers
        server/controllers/login.c
        server/controllers/save_file.c
        server/controllers/get_contests_problems.c
        server/controllers/register_for_contest.c
        server/controllers/users_contests.c
        server/controllers/get_contests.c
        server/controllers/get_contest.c
        server/controllers/get_problem.c
        server/controllers/signup.c
        server/controllers/problem_creation.c
        server/controllers/submit_problem.c
        server/controllers/check_result.c server/controllers/get_problems.c server/controllers/create_test_case.c server/controllers/create_contest.c server/controllers/add_problem_to_contest.c)

add_library(
        client_controllers
        client/client/ui.c
        client/controllers/register_user.c
        client/controllers/client_methods.c
        client/controllers/submit_solution.c
)


add_executable(os_project_server ${SERVER_SOURCE_FILES})
add_executable(os_project_file_server ${FILE_SERVER_SOURCE_FILES})
add_executable(os_project_client ${CLIENT_SOURCE_FILES})

target_link_libraries(os_project_server ${PostgreSQL_LIBRARIES})
target_link_libraries(os_project_file_server ${PostgreSQL_LIBRARIES})

target_link_libraries(os_project_file_server lib db vendor model server controllers)
target_link_libraries(os_project_server lib db vendor model server controllers)
target_link_libraries(os_project_client lib vendor client client_controllers)
