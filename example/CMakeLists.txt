cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(example VERSION 1.0.0)

add_executable(example main.cpp)
target_link_libraries(example PUBLIC Templi)