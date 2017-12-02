cmake_minimum_required(VERSION 3.8)
project(os_project)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES server/main.c)

include_directories(lib server/models vendor/cJSON config)
include_directories(vendor)

include(server/pgsqlFind.cmake)

add_library(lib lib/helpers.c lib/dictionary.c lib/_string.c lib/DataBase.c)
add_library(vendor vendor/cJSON/cJSON.c)
add_library(model server/models/user.c server/models/problem.c server/models/problem.h)

link_libraries(lib vendor model)

add_executable(os_project ${SOURCE_FILES})

target_link_libraries(os_project ${PostgreSQL_LIBRARIES})