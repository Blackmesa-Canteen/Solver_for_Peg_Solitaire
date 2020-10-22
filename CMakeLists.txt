cmake_minimum_required(VERSION 3.17)
project(Assigment3_Code C)

set(CMAKE_C_STANDARD 99)

add_executable(Assigment3_Code src/ai.c src/ai.h src/hashtable.c src/hashtable.h src/layouts.h src/stack.c
        src/stack.h src/utils.c src/utils.h peg_solitaire.c)