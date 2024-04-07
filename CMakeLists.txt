cmake_minimum_required(VERSION 3.24.2)
project(untitled C)

set(CMAKE_C_STANDARD 17)

# If you are using CLion, setting the C_STANDARD property ensures that it will understand the C17 standard.
# For add_executable, typically only source files are listed.
add_executable(untitled src/main.c src/carddeck.c)

# If you need to include directories for your project, you can use include_directories like so:
include_directories(src)

# If you have resources or additional files to copy to the binary directory, you could add custom commands.
# For example, if you need to copy the `cards.txt` from the `rsc` directory to the working directory of the executable:
file(COPY ${CMAKE_SOURCE_DIR}/rsc/cards.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/rsc)
