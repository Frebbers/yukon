cmake_minimum_required(VERSION 3.24.2)
project(Yukon C)

set(CMAKE_C_STANDARD 17)

# If you are using CLion, setting the C_STANDARD property ensures that it will understand the C17 standard.
# For add_executable, typically only source files are listed.
add_executable(Yukon src/main.c src/carddeck.c
        src/board.c
        src/board.h
        src/LD.c
        src/LD.h
        src/SW.c
        src/SW.h
        src/SR.c
        src/Phases.c
        src/SI.c
        src/renderTools.c
        src/renderTools.h
)

# If you need to include directories for your project, you can use include_directories like so:
#find_package(SDL2 REQUIRED)
#SDL2_DIR (${PROJECT_SOURCE_DIR}/src/lib/cmake/SDL2)
Include_directories(src)
include_directories(src/include/SDL2)
link_directories(${PROJECT_SOURCE_DIR}/src/lib)
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(Yukon
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(Yukon
        PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,
        SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
file(COPY ${CMAKE_SOURCE_DIR}/rsc/UnShuffledcards.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/rsc)
file(GLOB GRAPHICS_FILES "${CMAKE_SOURCE_DIR}/rsc/graphics/*")
file(COPY ${GRAPHICS_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/rsc/graphics/")