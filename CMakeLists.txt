cmake_minimum_required(VERSION 3.24)
project(project C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

add_executable(project main.c funcs.c main.h list.c list.h structs.h funcs.h)
