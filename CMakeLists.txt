cmake_minimum_required(VERSION 3.18)

project(templi_tools VERSION 4.2.0)

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

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# list of options
option(TEMPLI_LIB_BUILD "Build Templi lib" ON)
option(CMAKE_BUILD_SHARED_LIBS "Build Templi as a shared library" OFF)
option(TEMPLI_LIB_INSTALL "Install Templi lib" ${TEMPLI_IS_MAIN_PROJECT})
option(TEMPLI_CLI_BUILD "Build Templi cli" ${TEMPLI_IS_MAIN_PROJECT})
option(TEMPLI_CLI_INSTALL "Install Templi cli" ${TEMPLI_CLI_BUILD})
option(TEMPLI_BUILD_TESTS "Build templi test" ${TEMPLI_IS_MAIN_PROJECT})

if(WIN32)
  add_compile_options(WIN32)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(TEMPLI_BUILD_TESTS OFF)
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
  enable_testing()
  add_subdirectory(tests)
endif()