#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <algorithm>
#include <utility>

#include "fs_utils.hpp"
#include "parser.hpp"
#include "utils.hpp"

using namespace Templi;

static const std::string GIT_SUFFIX = ".git";

void Templi::generate(std::string template_path,
	std::string output_path,
	std::map<std::string, std::string> values,
	std::vector<std::string> ignored_path)
{
	Templi::copy_folder(template_path, output_path);

	std::vector<std::string> files = Templi::get_files_with_placeholder(output_path, ignored_path);

	if (files.empty())
		throw Templi::Exception("Folder empty or no words inside {{}} was found");

	for (auto file : files)
	{
		Templi::replace_placeholders_in_file(file, file, values);
	}
	Templi::replace_folder_filename_placeholders(output_path, values, ignored_path);
}

void Templi::configure(std::string template_path)
{
	TempliConfig templi_config;
	templi_config.m_excludes.push_back(TEMPLI_CONFIG_NAME);

	if (std::filesystem::exists(Templi::create_config_path(template_path)))
	{
		TempliConfig configure_templi_config(template_path);
		templi_config.m_excludes = configure_templi_config.m_excludes;
	}

	std::vector<std::string> files =
		Templi::get_files_with_placeholder(template_path, templi_config.m_excludes);
	std::set<std::string> words{};

	if (files.empty())
		throw Templi::Exception("Folder empty or no words inside {{}} was found");

	for (auto file : files)
	{
		std::set<std::string> words_found_in_file_name =
			Templi::extract_placeholders_from_text(file);
		std::set<std::string> words_found = Templi::extract_placeholders_from_file(file);

		for (auto word_found : words_found_in_file_name)
			words_found.insert(word_found);

		if (words_found.empty())
			templi_config.m_excludes.push_back(file.substr(template_path.size() + 1));

		for (auto word_found : words_found)
			words.insert(word_found);
	}

	for (auto word : words)
	{
		Key new_key;
		new_key.m_label = "What is the value of : " + word + " ?";
		new_key.m_name = word;
		new_key.m_type = KeyType::INPUT;
		templi_config.m_keys.push_back(new_key);
	}
	templi_config.save(template_path);
}

void Templi::generate_with_templi_config(std::string template_path,
	std::string output_path,
	std::function<std::string(Key key)> get_key_value)
{
	std::map<std::string, std::string> values{ { "TEMPLI_OUTPUT_FOLDER", output_path } };
	TempliConfig templi_config(template_path);

	std::for_each(templi_config.m_keys.begin(),
		templi_config.m_keys.end(),
		[&](Key &key) { values.insert(std::make_pair(key.m_name, get_key_value(key))); });

	Templi::execute_scripts(values, templi_config.m_before);
	Templi::generate(template_path, output_path, values, templi_config.m_excludes);
	Templi::delete_file(Templi::create_config_path(output_path));
	Templi::execute_scripts(values, templi_config.m_after);
}
