cmake_minimum_required(VERSION 3.8)
project(client_side)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c cJSON client)
add_executable(client_side ${SOURCE_FILES})