cmake_minimum_required(VERSION 3.8)
project(server_side)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c server cJSON)
add_executable(server_side ${SOURCE_FILES})