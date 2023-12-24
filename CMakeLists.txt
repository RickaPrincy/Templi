cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Templi VERSION 3.0.0)

option(TEMPLI_CLI_BUILD "Build Templi cli" OFF)
option(TEMPLI_CLI_INSTALL "Install Templi cli" OFF)
option(TEMPLI_LIB "Build Templi lib" ON)
option(TEMPLI_LIB_INSTALL "Install Templi lib" OFF)
option(TEMPLI_TEST "Build templi test" OFF)

if (WIN32)
    set(TEMPLI_SEPARATOR "\\")
else ()
    set(TEMPLI_SEPARATOR "/")
endif()

set(TEMPLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(TempliConfig.h.in ${TEMPLI_SOURCE_DIR}/include/Templi/TempliConfig.hpp)

include_directories(${TEMPLI_SOURCE_DIR}/include)
include_directories(${TEMPLI_SOURCE_DIR}/external/TColor/include)
include_directories(${TEMPLI_SOURCE_DIR}/external/RCli/include)

add_subdirectory(external/RCli)
add_subdirectory(src)

if(TEMPLI_CLI_BUILD)
    add_subdirectory(cli)
endif()

if(TEMPLI_TEST)
    add_subdirectory(external/googletest)
    add_subdirectory(tests)
endif()

set(CPACK_PACKAGE_VENDOR "RickaPrincy <https://github.com/RickaPrincy")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Templi is a groundbreaking tool designed to expedite the template file generation process")
include(CPack)