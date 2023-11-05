set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/${BINARY}/*.hpp")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${BINARY} STATIC ${SOURCES} ${HEADERS})

install(TARGETS  ${BINARY} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/Templi)