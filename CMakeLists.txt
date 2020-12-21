cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Curso VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CURSES_LIBRARIES ncurses)

include_directories(include)
add_subdirectory(src)
