cmake_minimum_required(VERSION 3.24.2)
project(untitled C)

set(CMAKE_C_STANDARD 17)

# If you are using CLion, setting the C_STANDARD property ensures that it will understand the C17 standard.
# For add_executable, typically only source files are listed.
add_executable(untitled src/main.c src/carddeck.c
        src/board.c
        src/board.h
        src/LD.c
        src/LD.h
        src/SW.c
        src/SW.h
        src/SR.c
)

# If you need to include directories for your project, you can use include_directories like so:
include_directories(src)

file(COPY ${CMAKE_SOURCE_DIR}/rsc/cards.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/rsc)
