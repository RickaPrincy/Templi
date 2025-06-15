#pragma once

#include <string>

auto FIXTURE(std::string prefix, std::string file) -> std::string;
auto ASSERT_EQ_DIRECTORY(std::string expected, std::string actual) -> void;
auto get_templi_cli_path() -> std::string;
