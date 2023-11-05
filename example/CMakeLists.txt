cmake_minimum_required(VERSION 3.27)
project(example)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Templi)