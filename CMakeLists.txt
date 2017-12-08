cmake_minimum_required(VERSION 3.8)
project(os_project)

set(CMAKE_C_STANDARD 11)

set(SERVER_SOURCE_FILES server/main.c)
set(CLIENT_SOURCE_FILES client/main.c)

include_directories(lib server/models vendor/cJSON config server/server client/client)
include_directories(vendor)

include(server/pgsqlFind.cmake)

add_library(lib lib/helpers.c lib/dictionary.c lib/_string.c)
add_library(db lib/DataBase.c)
add_library(vendor vendor/cJSON/cJSON.c)
add_library(model server/models/user.c server/models/problem.c server/models/category.c)
add_library(server server/server/server.c)
add_library(client client/client/client.c)

link_libraries(lib db vendor model server)

add_executable(os_project_server ${SERVER_SOURCE_FILES})
add_executable(os_project_client ${CLIENT_SOURCE_FILES})

target_link_libraries(os_project_server lib db vendor model server)
target_link_libraries(os_project_server ${PostgreSQL_LIBRARIES})
target_link_libraries(os_project_client lib vendor client)
