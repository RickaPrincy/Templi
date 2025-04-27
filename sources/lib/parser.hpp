#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

namespace Templi
{
	std::set<std::string> extract_placeholders_from_text(std::string text);

	std::string replace_placeholders_in_text(std::string text,
		std::map<std::string, std::string> values);

	std::set<std::string> extract_placeholders_from_file(std::string file_path);

	void replace_placeholders_in_file(std::string file_path,
		std::string output_path,
		std::map<std::string, std::string> values);

	void replace_folder_filename_placeholders(std::string folder_path,
		std::map<std::string, std::string> values,
		std::vector<std::string> excludes);
}  // namespace Templi
