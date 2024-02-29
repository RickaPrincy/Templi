set(CLI_SOURCES templi.cpp)
add_executable(${TEMPLI_CLI_NAME} ${CLI_SOURCES})

target_include_directories(${TEMPLI_CLI_NAME}
                           PRIVATE ${TEMPLI_SOURCE_DIR}/include)

target_link_libraries(${TEMPLI_CLI_NAME} PRIVATE ${TEMPLI_LIB_NAME})

if(TEMPLI_CLI_INSTALL)
  install(TARGETS ${TEMPLI_CLI_NAME} DESTINATION bin)
endif()
