cmake_minimum_required(VERSION 3.8)
project(os_project)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c)

include(pgsqlFind.cmake)
include_directories(vendor/cJSON)

link_libraries(${PostgreSQL_LIBRARIES})

add_executable(os_project ${SOURCE_FILES} DB_CONFIG.h helpers.c helpers.h DataBase.c DataBase.h vendor/cJSON/cJSON.c)
