cmake_minimum_required(VERSION 3.22.1)

project(GRAPHICS)

add_executable(main main.cpp)

add_subdirectory(src)

target_link_libraries(main graphics)