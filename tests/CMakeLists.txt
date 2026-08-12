find_package(GTest CONFIG REQUIRED)

# Copy fixtures
file(COPY ${CMAKE_SOURCE_DIR}/tests/fixtures
        DESTINATION ${CMAKE_BINARY_DIR}/tests)

set(TEST_SOURCES
        utils.cpp
        utils.hpp
        lib/configure.cpp
        lib/generate_with_args.cpp
        lib/generate_with_templi_config.cpp
        lib/fs_utils/get_files_with_placeholder.cpp
        lib/parser/extract_placeholders_from_file.cpp
        lib/parser/extract_placeholders_from_text.cpp
        lib/parser/replace_folder_filename_placeholders.cpp
        lib/parser/replace_placeholders_in_file.cpp
        lib/parser/replace_placeholders_in_text.cpp
        cli/configure.cpp
        cli/generate.cpp
)

add_executable(${TEMPLI_TEST_NAME} ${TEST_SOURCES})

target_include_directories(
  ${TEMPLI_TEST_NAME}
  PRIVATE "${TEMPLI_SOURCE_DIR}/include"
  PRIVATE "${TEMPLI_SOURCE_DIR}/sources/lib"
)

target_link_directories(${TEMPLI_TEST_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(
  ${TEMPLI_TEST_NAME}
  PRIVATE ${TEMPLI_LIB_NAME}
  PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEMPLI_TEST_NAME})