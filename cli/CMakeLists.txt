file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
add_executable(templi ${SOURCES})

target_link_directories(templi 
    PUBLIC ${TEMPLI_SOURCE_DIR}/build/src
)

target_link_libraries(templi 
    PUBLIC ${TEMPLI_LIB_NAME}
    PUBLIC rcli
)

if(TEMPLI_CLI_INSTALL)
    install(TARGETS templi DESTINATION bin)
endif()