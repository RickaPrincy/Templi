set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/Templi/*.hpp")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${BINARY} STATIC ${SOURCES})

set_target_properties(${BINARY} PROPERTIES 
    PUBLIC_HEADER ${HEADERS} 
)

install(TARGETS 
    ${BINARY} DESTINATION lib
    PUBLIC_HEADER DESTINATION include/Templi
)