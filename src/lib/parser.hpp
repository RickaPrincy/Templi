#pragma once

#include <map>
#include <set>
#include <string>

namespace Templi
{
	std::set<std::string> extract_placeholders(std::string text);

	std::string replace_placeholders_in_text(std::string text,
		std::map<std::string, std::string> values);

	std::set<std::string> extract_placeholders_from_file(std::string file_path);

	void replace_placeholders_in_file(std::string file_path,
		std::string output_path,
		std::map<std::string, std::string> values);

}  // namespace Templi
