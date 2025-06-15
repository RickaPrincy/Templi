#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <algorithm>

#include "fs_utils.hpp"
#include "parser.hpp"
#include "utils.hpp"

static const std::string GIT_SUFFIX = ".git";

namespace Templi
{
	auto generate(const std::string &template_path,
		const std::string &output_path,
		const std::map<std::string, std::string> &values,
		const std::vector<std::string> &excludes) -> void
	{
		copy_folder(template_path, output_path);

		std::vector<std::string> files = get_files_with_placeholder(output_path, excludes);

		if (files.empty())
		{
			throw Exception("Folder empty or no words inside {{}} was found");
		}

		for (const auto &file : files)
		{
			replace_placeholders_in_file(file, file, values);
		}
		replace_folder_filename_placeholders(output_path, values, excludes);
	}

	auto configure(const std::string &template_path) -> void
	{
		TempliConfig templi_config;
		templi_config.m_excludes.emplace_back(TEMPLI_CONFIG_NAME);

		if (std::filesystem::exists(create_config_path(template_path)))
		{
			TempliConfig configure_templi_config(template_path);
			templi_config.m_excludes = configure_templi_config.m_excludes;
		}

		std::vector<std::string> files =
			get_files_with_placeholder(template_path, templi_config.m_excludes);
		std::set<std::string> words{};

		if (files.empty())
		{
			throw Exception("Folder empty or no words inside {{}} was found");
		}

		for (const auto &file : files)
		{
			std::set<std::string> words_found_in_file_name = extract_placeholders_from_text(file);
			std::set<std::string> words_found = extract_placeholders_from_file(file);

			for (const auto &word_found : words_found_in_file_name)
			{
				words_found.insert(word_found);
			}

			if (words_found.empty())
			{
				templi_config.m_excludes.push_back(file.substr(template_path.size() + 1));
			}

			for (const auto &word_found : words_found)
			{
				words.insert(word_found);
			}
		}

		for (const auto &word : words)
		{
			Placeholder new_placeholder;
			new_placeholder.m_label = word;
			new_placeholder.m_name = word;
			new_placeholder.m_type = PlaceholderType::TEXT;
			templi_config.m_placeholders.push_back(new_placeholder);
		}
		templi_config.save(template_path);
	}

	auto generate_with_templi_config(const std::string &template_path,
		const std::string &output_path,
		std::function<std::string(Placeholder placeholder)> get_placeholder_value) -> void
	{
		std::map<std::string, std::string> values{ { "TEMPLI_OUTPUT_FOLDER", output_path } };
		TempliConfig templi_config(template_path);

		std::for_each(templi_config.m_placeholders.begin(),
			templi_config.m_placeholders.end(),
			[&](Placeholder &placeholder)
			{
				values.insert(
					std::make_pair(placeholder.m_name, get_placeholder_value(placeholder)));
			});

		execute_scripts(values, templi_config.m_before);
		generate(template_path, output_path, values, templi_config.m_excludes);
		delete_file(create_config_path(output_path));
		execute_scripts(values, templi_config.m_after);
	}
}  // namespace Templi
