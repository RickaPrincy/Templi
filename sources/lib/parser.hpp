#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

namespace Templi
{
	auto extract_placeholders_from_text(const std::string &text) -> std::set<std::string>;

	auto extract_placeholders_from_file(const std::string &file_path) -> std::set<std::string>;

	auto replace_placeholders_in_text(const std::string &text,
		const std::map<std::string, std::string> &values) -> std::string;

	auto replace_placeholders_in_file(const std::string &file_path,
		const std::string &output_path,
		const std::map<std::string, std::string> &values) -> void;

	auto replace_folder_filename_placeholders(const std::string &folder_path,
		const std::map<std::string, std::string> &values,
		const std::vector<std::string> &excludes) -> void;
}  // namespace Templi
