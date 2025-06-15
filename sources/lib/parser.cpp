#include "parser.hpp"

#include <algorithm>
#include <iterator>

#include "fs_utils.hpp"

namespace fs = std::filesystem;

namespace Templi
{
	static auto process_placeholder(const std::string &text,
		const std::map<std::string, std::string> &values,
		std::set<std::string> &words) -> std::string
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

			size_t word_length = end_pos - start_pos;
			std::string word = text.substr(start_pos, word_length);

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

	auto extract_placeholders_from_text(const std::string &text) -> std::set<std::string>
	{
		std::set<std::string> words;
		process_placeholder(text, {}, words);
		return words;
	}

	auto replace_placeholders_in_text(const std::string &text,
		const std::map<std::string, std::string> &values) -> std::string
	{
		std::set<std::string> words;
		return process_placeholder(text, values, words);
	}

	auto extract_placeholders_from_file(const std::string &file_path) -> std::set<std::string>
	{
		std::set<std::string> words;
		process_for_each_line(file_path,
			[&](const std::string &line_content)
			{
				for (const auto &word : extract_placeholders_from_text(line_content))
				{
					words.insert(word);
				}
			});
		return words;
	}

	auto replace_placeholders_in_file(const std::string &file_path,
		const std::string &output_path,
		const std::map<std::string, std::string> &values) -> void
	{
		std::stringstream file_parsed_content;

		process_for_each_line(file_path,
			[&](const std::string &line_content)
			{ file_parsed_content << replace_placeholders_in_text(line_content, values) << "\n"; });

		save_file(output_path, file_parsed_content.str());
	}

	static void replace_folder_filename_placeholders_process(const std::string &folder_path,
		const std::map<std::string, std::string> &values,
		const std::vector<std::string> &exclude_paths)
	{
		fs::path filepath = fs::path(folder_path);
		auto it = std::find(exclude_paths.begin(), exclude_paths.end(), filepath.string());
		if (it != exclude_paths.end())
		{
			return;
		}

		std::string filename = filepath.filename();
		std::string new_file_name = replace_placeholders_in_text(filename, values);

		if (filename != new_file_name)
		{
			fs::path new_path = filepath.parent_path() / new_file_name;
			rename(filepath.string(), new_path.string());
			return replace_folder_filename_placeholders_process(new_path, values, exclude_paths);
		}

		if (!fs::exists(filepath) || !fs::is_directory(filepath))
		{
			return;
		}

		for (const auto &child_file : fs::directory_iterator(filepath))
		{
			replace_folder_filename_placeholders_process(
				child_file.path().string(), values, exclude_paths);
		}
	}

	auto replace_folder_filename_placeholders(const std::string &folder_path,
		const std::map<std::string, std::string> &values,
		const std::vector<std::string> &exclude_paths) -> void
	{
		std::vector<std::string> relative_exclude_paths{};
		std::transform(exclude_paths.begin(),
			exclude_paths.end(),
			std::back_inserter(relative_exclude_paths),
			[&](const std::string &path)
			{
				return (std::filesystem::path(folder_path) / std::filesystem::path(path)).string();
			});

		replace_folder_filename_placeholders_process(folder_path, values, relative_exclude_paths);
	}
}  // namespace Templi
