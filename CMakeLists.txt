cmake_minimum_required(VERSION 2.8)

project(garden)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(garden ${PROJECT_SOURCE_DIR}/garden.c)

find_package(Curses)
if (CURSES_FOUND)
  include_directories(${CURSES_INCLUDE_DIRS})
  target_link_libraries(garden ${CURSES_LIBRARIES})
endif (CURSES_FOUND)
