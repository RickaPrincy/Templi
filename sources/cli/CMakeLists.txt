set(CLI_SOURCES templi.cpp utils.cpp)

add_executable(${TEMPLI_CLI_NAME})

target_sources(${TEMPLI_CLI_NAME} PRIVATE ${CLI_SOURCES})

target_include_directories(${TEMPLI_CLI_NAME}
                           PRIVATE ${TEMPLI_SOURCE_DIR}/include)

target_link_libraries(${TEMPLI_CLI_NAME} PRIVATE rcli)
target_link_libraries(${TEMPLI_CLI_NAME} PRIVATE cpp_inquirer)
target_link_libraries(${TEMPLI_CLI_NAME} PRIVATE ${TEMPLI_LIB_NAME})

set_target_properties(${TEMPLI_CLI_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                    "${CMAKE_BINARY_DIR}/bin")

if(TEMPLI_CLI_INSTALL)
  install(TARGETS ${TEMPLI_CLI_NAME} DESTINATION bin)
endif()
