find_package(Curses REQUIRED)

# add the executable
add_executable(tetris Main.cpp)

target_link_libraries(tetris ${CURSES_LIBRARIES})