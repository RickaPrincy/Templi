#include "parser.hpp"

#include "fs_utils.hpp"

using namespace Templi;

std::string Templi::brackets_parser(std::string text,
	const std::map<std::string, std::string> values,
	std::set<std::string> &words)
{
	std::string result;
	size_t pos = 0;

	while (pos < text.length())
	{
		size_t open_brace_pos = text.find("{{", pos);
		size_t escape_pos = text.find("\\{", pos);

		// Handle \{
		if (escape_pos != std::string::npos &&
			(open_brace_pos == std::string::npos || escape_pos < open_brace_pos))
		{
			result += text.substr(pos, escape_pos - pos) + '{';
			pos = escape_pos + 2;
			continue;
		}

		// If there's no more {{, just add the remaining part of the text to result
		if (open_brace_pos == std::string::npos)
		{
			result += text.substr(pos);
			break;
		}

		// Add the text before {{ to the result
		result += text.substr(pos, open_brace_pos - pos);

		// Find the closing braces }}
		size_t start_pos = open_brace_pos + 2;
		size_t end_pos = text.find("}}", start_pos);

		if (end_pos == std::string::npos)
		{
			result += text.substr(open_brace_pos);
			break;
		}

		size_t wordLength = end_pos - start_pos;
		std::string word = text.substr(start_pos, wordLength);

		words.insert(word);
		auto it = values.find(word);

		if (it != values.end())
		{
			result += it->second;
			pos = end_pos + 2;
		}
		else
		{
			result += "{{" + word + "}}";
			pos = end_pos + 2;
		}
	}

	return result;
}

std::set<std::string> Templi::get_brackets_words(std::string text)
{
	std::set<std::string> words;
	brackets_parser(text, {}, words);
	return words;
}

std::string Templi::replace_brackets_words(std::string text,
	std::map<std::string, std::string> values)
{
	std::set<std::string> words;
	return brackets_parser(text, values, words);
}

std::set<std::string> Templi::file_get_brackets_words(std::string file_path)
{
	std::set<std::string> words;
	process_for_each_line(file_path,
		[&](const std::string &line_content)
		{
			for (auto word : get_brackets_words(line_content))
				words.insert(word);
		});
	return words;
}

void Templi::file_brackets_parser(std::string file_path,
	std::string output_path,
	std::map<std::string, std::string> values)
{
	std::stringstream file_parsed_content;

	process_for_each_line(file_path,
		[&](const std::string &line_content)
		{ file_parsed_content << replace_brackets_words(line_content, values) << "\n"; });

	save_file(output_path, file_parsed_content.str());
}
