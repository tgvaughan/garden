cmake_minimum_required(VERSION 2.8)

project(garden)

set(src ${CMAKE_SOURCE_DIR}/src)

add_library(garden_objs OBJECT ${src}/ui.c ${src}/world.c)
add_executable(garden $<TARGET_OBJECTS:garden_objs> ${src}/main.c)

find_package(Curses)
if (CURSES_FOUND)
  include_directories(${CURSES_INCLUDE_DIRS})
  target_link_libraries(garden ${CURSES_LIBRARIES})
endif (CURSES_FOUND)
