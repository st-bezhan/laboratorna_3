cmake_minimum_required(VERSION 3.28)
project(laboratorna_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(laboratorna_3 main.c
        calculation_functions.h
        calculation_functions.c
        io_functions.h
        io_functions.c)
