cmake_minimum_required(VERSION 3.22.1)

set(CXX_STANDARD 20)

project(rasterizer)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lodepng
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/stb
)

target_link_libraries(${PROJECT_NAME} lodepng stb)
