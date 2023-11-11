file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
add_executable(templi ${SOURCES})

target_include_directories(templi 
    PUBLIC ${CMAKE_SOURCE_DIR}/external/TColor/include
)
target_link_directories(templi PUBLIC ${CMAKE_SOURCE_DIR}/build/src)
target_link_libraries(templi PUBLIC ${PROJECT_NAME})

if(TEMPLI_CLI_INSTALL)
    install(TARGETS templi DESTINATION bin)
endif()