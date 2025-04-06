#pragma once

#include <map>
#include <set>
#include <string>

namespace Templi
{
	std::string brackets_parser(std::string text,
		const std::map<std::string, std::string> values,
		std::set<std::string> &words);
	std::set<std::string> get_brackets_words(std::string text);
	std::string replace_brackets_words(std::string text, std::map<std::string, std::string> values);

	void file_brackets_parser(std::string file_path,
		std::string output_path,
		std::map<std::string, std::string> values);
	std::set<std::string> file_get_brackets_words(std::string file_path);
}  // namespace Templi
