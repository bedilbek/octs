cmake_minimum_required(VERSION 3.8)
project(os_project)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c lib/dictionary.c lib/dictionary.h network/main.c network/server/server.c network/server/server.h network/client/client.c network/client/client.h)

add_library(lib lib/_string.c lib/dictionary.c)
add_library(vendor vendor/cJSON/cJSON.c)
add_library(helper helpers.c)

include(pgsqlFind.cmake)

link_libraries(${PostgreSQL_LIBRARIES} lib vendor helper)

add_executable(os_project ${SOURCE_FILES} DB_CONFIG.h DataBase.c DataBase.h network/main.c network/client/client.c network/client/client.h)
