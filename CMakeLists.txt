cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Templi VERSION 1.0.0)

configure_file(TempliConfig.h.in ${CMAKE_SOURCE_DIR}/include/Templi/TempliConfig.hpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(external/googletest)
add_subdirectory(src)
add_subdirectory(tests)
