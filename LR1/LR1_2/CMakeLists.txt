cmake_minimum_required(VERSION 3.28)
project(LR1_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(LR1_2 main.c
        constantCalculation.c
        constantCalculation.h
        parsing.c
        parsing.h
        states.h)

target_link_libraries(LR1_2 m)