cmake_minimum_required(VERSION 3.15)
project(amaze-d VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

include_directories(include)

set(SOURCES
    src/main.c
    src/core/engine.c
    src/core/pathfinding.c
    src/core/room.c
    src/parser/parser.c
    src/parser/cleanup.c
    src/utils/string.c
    src/utils/io.c
    src/visual/display.c
    src/visual/stats.c
)

add_executable(amaze-d ${SOURCES})

if(WIN32)
    target_compile_definitions(amaze-d PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

install(TARGETS amaze-d DESTINATION bin)
