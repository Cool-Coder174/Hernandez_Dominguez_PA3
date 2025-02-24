cmake_minimum_required(VERSION 3.30)
project(Hernandez_Dominguez_PA3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Hernandez_Dominguez_PA3 main.c
        musicManager.h
        musicManager.c
        testFunctions.h
        testFunctions.c)
