# rcli and cpp_inquirer are header-only: nothing to install. An installed version is used when
# it is recent enough, otherwise the pinned release is downloaded at configure time.
include(FetchContent)

find_package(rcli 2.1 QUIET)
if(NOT rcli_FOUND)
  FetchContent_Declare(
    rcli
    URL https://github.com/RickaPrincy/rcli/archive/refs/tags/v2.1.0.tar.gz
    URL_HASH SHA256=c6e0f120547272c87ba8ccb795c73dd4c24243974f3e86d4a0e9e3da0756109e
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
  FetchContent_MakeAvailable(rcli)
endif()

find_package(cpp_inquirer 0.1 QUIET)
if(NOT cpp_inquirer_FOUND)
  FetchContent_Declare(
    cpp_inquirer
    URL https://github.com/RickaPrincy/cpp_inquirer/archive/refs/tags/v0.1.0.tar.gz
    URL_HASH SHA256=f6faf13e0454a76a71028f7c1da93fea4d75392166e95179cff7e15b4a7323b2
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
  FetchContent_MakeAvailable(cpp_inquirer)
endif()

set(CLI_SOURCES templi.cpp utils.cpp)

add_executable(${TEMPLI_CLI_NAME})

target_sources(${TEMPLI_CLI_NAME} PRIVATE ${CLI_SOURCES})

target_include_directories(${TEMPLI_CLI_NAME}
                           PRIVATE ${TEMPLI_SOURCE_DIR}/include)

target_link_libraries(${TEMPLI_CLI_NAME} PRIVATE rcli::rcli)
target_link_libraries(${TEMPLI_CLI_NAME} PRIVATE cpp_inquirer::cpp_inquirer)
target_link_libraries(${TEMPLI_CLI_NAME} PRIVATE ${TEMPLI_LIB_NAME})

set_target_properties(${TEMPLI_CLI_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                    "${CMAKE_BINARY_DIR}/bin")

if(TEMPLI_CLI_INSTALL)
  install(TARGETS ${TEMPLI_CLI_NAME} DESTINATION bin)
endif()
