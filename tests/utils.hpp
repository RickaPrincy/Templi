#pragma once

#include <string>

std::string FIXTURE(std::string prefix, std::string file);
void ASSERT_EQ_DIRECTORY(std::string expected, std::string actual);
std::string get_templi_cli_path();
