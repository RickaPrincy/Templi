cmake_minimum_required(VERSION 3.18)

project(templi_tools VERSION 4.0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(rcli REQUIRED VERSION 2.0.21)

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
option(BUILD_SHARED_LIBS "Build Templi as a shared library"
       ${TEMPLI_IS_MAIN_PROJECT})
option(TEMPLI_CLI_BUILD "Build Templi cli" ON)
option(TEMPLI_CLI_INSTALL "Install Templi cli" ${TEMPLI_IS_MAIN_PROJECT})
option(TEMPLI_LIB_BUILD "Build Templi lib" ON)
option(TEMPLI_LIB_INSTALL "Install Templi lib" ${TEMPLI_IS_MAIN_PROJECT})
option(TEMPLI_TEST "Build templi test" ${TEMPLI_IS_MAIN_PROJECT})

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(WIN32)
  add_compile_options(WIN32)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(TEMPLI_TEST OFF)
endif()

if(TEMPLI_IS_MAIN_PROJECT)
  configure_file(${TEMPLI_SOURCE_DIR}/.templates/PKGBUILD/cli/PKGBUILD.in
                 ${TEMPLI_SOURCE_DIR}/PKGBUILD/cli/PKGBUILD @ONLY)

  configure_file(${TEMPLI_SOURCE_DIR}/.templates/PKGBUILD/lib/PKGBUILD.in
                 ${TEMPLI_SOURCE_DIR}/PKGBUILD/lib/PKGBUILD @ONLY)

  configure_file(${TEMPLI_SOURCE_DIR}/.templates/scripts/install.sh.in
                 ${TEMPLI_SOURCE_DIR}/install.sh @ONLY)

  configure_file(${TEMPLI_SOURCE_DIR}/.templates/scripts/create-release.sh.in
                 ${TEMPLI_SOURCE_DIR}/create-release.sh @ONLY)

  configure_file(
    ${TEMPLI_SOURCE_DIR}/.templates/${TEMPLI_LIB_NAME}CliConfig.hpp.in
    ${TEMPLI_SOURCE_DIR}/include/${TEMPLI_LIB_NAME}/${TEMPLI_LIB_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(sources)

# Test configuration
if(TEMPLI_TEST)
  set(SUBMODULES external/googletest)
  find_package(Git REQUIRED)

  foreach(submodule ${SUBMODULES})
    execute_process(
      COMMAND ${GIT_EXECUTABLE} submodule update --init ${submodule}
      WORKING_DIRECTORY ${TEMPLI_SOURCE_DIR}
      RESULT_VARIABLE GIT_SUBMOD_RESULT)

    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(
        FATAL_ERROR
          "git submodule update --init  ${submodule} failed with ${GIT_SUBMOD_RESULT}, please checkout submodules"
      )
    endif()
  endforeach()

  add_subdirectory(external/googletest)
  add_subdirectory(tests)
endif()

execute_process(
  COMMAND git --version
  RESULT_VARIABLE GIT_RESULT
  OUTPUT_QUIET)

if(NOT GIT_RESULT EQUAL 0)
  message(FATAL_ERROR "git is required")
endif()

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES "${TEMPLI_SOURCE_DIR}/sources/lib/*.cpp"
       "${TEMPLI_SOURCE_DIR}/sources/cli/*.cpp"
       "${TEMPLI_SOURCE_DIR}/tests/*.cpp"
       "${TEMPLI_SOURCE_DIR}/tests/*.hpp"
       "${TEMPLI_SOURCE_DIR}/tests/cli/*.cpp"
       "${TEMPLI_SOURCE_DIR}/tests/lib/*.cpp"
       "${TEMPLI_SOURCE_DIR}/tests/lib/parser/*.cpp"
       "${TEMPLI_SOURCE_DIR}/tests/lib/fs_utils/*.cpp"
       "${TEMPLI_SOURCE_DIR}/tests/lib/*.cpp"
       "${TEMPLI_SOURCE_DIR}/include/Templi/*.hpp")
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format")
else()
  message(
    WARNING "clang-format not found. Clang-format target will not be available."
  )
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <https://github.com/RickaPrincy>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Templi is a tool that simplifies boilerplate creation and usage"
)
include(CPack)
