#include "utils.hpp"

#include <gtest/gtest.h>

#include <cstdio>
#include <filesystem>
#include <vector>

#include "fs_utils.hpp"

auto FIXTURE(std::string prefix, std::string file) -> std::string	// NOLINT
{
	return std::filesystem::path("fixtures") / std::filesystem::path(prefix) /
		   std::filesystem::path(file);
}

void ASSERT_EQ_DIRECTORY(std::string expected, std::string actual)	// NOLINT
{
	std::vector<std::string> expected_files = Templi::get_files_with_placeholder(expected);
	std::vector<std::string> actual_files = Templi::get_files_with_placeholder(actual);

	ASSERT_EQ(expected_files.size(), actual_files.size());

	for (size_t i = 0; i < expected_files.size(); i++)
	{
		ASSERT_EQ(expected_files[i].substr(expected.size()), actual_files[i].substr(actual.size()));

		std::vector<std::string> expected_lines{};
		std::vector<std::string> actual_lines{};

		Templi::process_for_each_line(
			expected_files[i], [&](const std::string &line) { expected_lines.push_back(line); });

		Templi::process_for_each_line(
			actual_files[i], [&](const std::string &line) { actual_lines.push_back(line); });

		ASSERT_EQ(expected_lines.size(), actual_lines.size());
		for (size_t j = 0; j < expected_lines.size(); j++)
		{
			ASSERT_EQ(expected_lines[j], actual_lines[j]);
		}
	}
}

auto get_templi_cli_path() -> std::string
{
	auto templi_cli_path =
		std::filesystem::current_path().parent_path().parent_path() / "bin" / "templi";
	return templi_cli_path.string();
}
