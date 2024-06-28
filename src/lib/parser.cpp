#include "parser.hpp"

#include "fs_utils.hpp"

using namespace Templi;

String Templi::brackets_parser(String text, const MapString values, SetString &words)
{
	String result = text;
	size_t pos = result.find("{{");

	while (pos != String::npos)
	{
		size_t start_pos = pos + 2;
		size_t end_pos = result.find("}}", start_pos);
		size_t escape_pos = text.find("\\{", pos);

		if (end_pos == String::npos)
			break;

		if (escape_pos != String::npos && escape_pos < start_pos)
		{
			result += text.substr(pos, escape_pos - pos) + '{';
			pos = escape_pos + 2;
			continue;
		}

		size_t wordLength = end_pos - start_pos;
		String word = result.substr(start_pos, wordLength);

		words.insert(word);
		auto it = values.find(word);

		if (it != values.end())
		{
			result.replace(pos, end_pos - pos + 2, it->second);
			pos = result.find("{{", pos + it->second.length());
		}
		else
			pos = result.find("{{", end_pos);
	}

	return result;
}

SetString Templi::get_brackets_words(String text)
{
	SetString words;
	brackets_parser(text, {}, words);
	return words;
}

String Templi::replace_brackets_words(String text, MapString values)
{
	SetString words;
	return brackets_parser(text, values, words);
}

SetString Templi::file_get_brackets_words(String file_path)
{
	SetString words;
	process_for_each_line(file_path,
		[&](const String &line_content)
		{
			for (auto word : get_brackets_words(line_content))
				words.insert(word);
		});
	return words;
}

void Templi::file_brackets_parser(String file_path, String output_path, MapString values)
{
	std::stringstream file_parsed_content;

	process_for_each_line(file_path,
		[&](const String &line_content)
		{ file_parsed_content << replace_brackets_words(line_content, values) << "\n"; });

	save_file(output_path, file_parsed_content.str());
}
