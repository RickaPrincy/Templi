file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.hpp")

set(TEMPLI_LIB_NAME templi_dev)

add_library(${TEMPLI_LIB_NAME} STATIC ${SOURCES} ${HEADERS})

if(TEMPLI_LIB_INSTALL)
    install(TARGETS ${LIB_NAME} DESTINATION lib)
    install(FILES ${HEADERS} DESTINATION include/templi)
endif()