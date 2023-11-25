cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Templi VERSION 1.0.1)

option(TEMPLI_CLI_BUILD "Build Templi cli" ON)
option(TEMPLI_CLI_INSTALL "Install Templi cli" ON)
option(TEMPLI_LIB "Build Templi lib" ON)
option(TEMPLI_LIB_INSTALL "Install Templi lib" ON)
option(TEMPLI_TEST "Build templi test" OFF)
option(TEMPLI_VERSION_BUILD "Build templi version" OFF)

if(TEMPLI_VERSION_BUILD)
    configure_file(TempliConfig.h.in ${CMAKE_SOURCE_DIR}/include/Templi/TempliConfig.hpp)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

if(TEMPLI_CLI_BUILD)
    add_subdirectory(bin)
endif()

if(TEMPLI_TEST)
    add_subdirectory(external/googletest)
    add_subdirectory(tests)
endif()

set(CPACK_PACKAGE_VENDOR "RickaPrincy <https://github.com/RickaPrincy")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Templi is a groundbreaking tool designed to expedite the template file generation process")
include(CPack)