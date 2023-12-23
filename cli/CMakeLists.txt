file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
add_executable(templi ${SOURCES})

target_include_directories(templi 
    PUBLIC ${TEMPLI_SOURCE_DIR}/external/TColor/include
    PUBLIC ${TEMPLI_SOURCE_DIR}/external/RCli/include
)

target_link_directories(templi 
    PUBLIC ${TEMPLI_SOURCE_DIR}/build/src
    PUBLIC ${TEMPLI_SOURCE_DIR}/external/RCli/src
)
target_link_libraries(templi 
    PUBLIC ${PROJECT_NAME}
    PUBLIC RCli 
)

if(TEMPLI_CLI_INSTALL)
    install(TARGETS templi DESTINATION bin)
endif()