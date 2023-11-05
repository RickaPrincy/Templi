cmake_minimum_required(VERSION 3.27)

project(Templi VERSION 0.9.0)

set(CMAKE_CXX_STANDARD 14)
configure_file(TempliConfig.h.in ${CMAKE_SOURCE_DIR}/include/Templi/TempliConfig.hpp)
add_subdirectory(src)