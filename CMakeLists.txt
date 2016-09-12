cmake_minimum_required(VERSION 2.8)

project(garden)

set(src ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_BUILD_TYPE Debug)

add_library(garden_objs OBJECT ${src}/ui.c ${src}/world.c)
add_executable(garden $<TARGET_OBJECTS:garden_objs> ${src}/main.c)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(garden ${CURSES_LIBRARIES})

target_link_libraries(garden m)
