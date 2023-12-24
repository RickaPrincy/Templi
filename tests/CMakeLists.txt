set(BINARY ${CMAKE_PROJECT_NAME}_test)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
add_executable(${BINARY} ${TEST_SOURCES})

target_include_directories(${BINARY} 
    PUBLIC ${TEMPLI_SOURCE_DIR}/include
    PUBLIC ${TEMPLI_SOURCE_DIR}/external/googleTest/include
)

target_link_directories( ${BINARY} 
    PUBLIC ${TEMPLI_SOURCE_DIR}/build/src 
    PUBLIC ${TEMPLI_SOURCE_DIR}/build/lib
)

target_link_libraries(${BINARY} 
    PUBLIC ${CMAKE_PROJECT_NAME}
    PUBLIC gtest
)