cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 17)

add_executable(untitled src/main.c
        src/carddeck.h
        src/carddeck.c
        src/gameLoader.c
        src/gameLoader.h)
