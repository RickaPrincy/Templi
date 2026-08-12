cmake_minimum_required(VERSION 3.18)

project(templi_tools VERSION 4.1.31)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TEMPLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEMPLI_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(TEMPLI_IS_MAIN_PROJECT ON)
endif()

# target names
set(TEMPLI_LIB_NAME Templi)
set(TEMPLI_LIB_VERSION ${PROJECT_VERSION})
set(TEMPLI_LIB_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

set(TEMPLI_CLI_NAME templi)
set(TEMPLI_CLI_VERSION ${PROJECT_VERSION})
set(TEMPLI_CLI_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

set(TEMPLI_TEST_NAME TempliTest)
set(TEMPLI_VERSION ${PROJECT_VERSION})
set(TEMPLI_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

# list of options
# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

option(TEMPLI_LIB_BUILD "Build Templi lib" ON)
option(TEMPLI_CLI_BUILD "Build Templi cli" OFF)
option(CMAKE_BUILD_SHARED_LIBS "Build Templi as a shared library" OFF)

option(TEMPLI_CLI_INSTALL "Install Templi cli" ${TEMPLI_CLI_BUILD})
option(TEMPLI_LIB_INSTALL "Install Templi lib" ${TEMPLI_LIB_BUILD})
option(TEMPLI_TEST "Build templi test" ${TEMPLI_IS_MAIN_PROJECT})

if(WIN32)
  add_compile_options(WIN32)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(TEMPLI_TEST OFF)
endif()

if(NOT CMAKE_BUILD_SHARED_LIBS)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

if(TEMPLI_IS_MAIN_PROJECT)
  configure_file(${TEMPLI_SOURCE_DIR}/.templates/PKGBUILD/cli/PKGBUILD.in
                 ${TEMPLI_SOURCE_DIR}/PKGBUILD/cli/PKGBUILD @ONLY)

  configure_file(${TEMPLI_SOURCE_DIR}/.templates/PKGBUILD/lib/PKGBUILD.in
                 ${TEMPLI_SOURCE_DIR}/PKGBUILD/lib/PKGBUILD @ONLY)

  configure_file(${TEMPLI_SOURCE_DIR}/.templates/scripts/create-release.sh.in
                 ${TEMPLI_SOURCE_DIR}/create-release.sh @ONLY)

  configure_file(
    ${TEMPLI_SOURCE_DIR}/.templates/${TEMPLI_LIB_NAME}CliConfig.hpp.in
    ${TEMPLI_SOURCE_DIR}/include/${TEMPLI_LIB_NAME}/${TEMPLI_LIB_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(sources)

# Test configuration
if(TEMPLI_BUILD_TESTS)
  add_subdirectory(tests)
endif()