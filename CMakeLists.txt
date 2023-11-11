cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Templi VERSION 1.0.0)

option(TEMPLI_CLI_BUILD "Build Templi cli" OFF)
option(TEMPLI_CLI_INSTALL "Install Templi cli" OFF)
option(TEMPLI_TEST "Build templi test" OFF)

configure_file(TempliConfig.h.in ${CMAKE_SOURCE_DIR}/include/Templi/TempliConfig.hpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

if(TEMPLI_CLI)
    add_subdirectory(bin)
endif()

if(TEMPLI_CLI)
    add_subdirectory(external/googletest)
    add_subdirectory(tests)
endif()

include(CPack)