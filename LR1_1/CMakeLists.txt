cmake_minimum_required(VERSION 3.28)
project(LR1 C)

set(CMAKE_C_STANDARD 17)

add_executable(LR1 main.c
        handlers.c
        handlers.h)
