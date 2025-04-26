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

	std::vector<std::string> files = Templi::get_folder_files(output_path, ignored_path);

	if (files.empty())
		throw Templi::Exception("Folder empty or no words inside {{}} was found");

	for (auto file : files)
	{
		Templi::replace_placeholders_in_file(file, file, values);
		std::filesystem::path file_path = std::filesystem::path(file);
		std::string filename = file_path.filename();
		std::string new_file_name = Templi::replace_placeholders_in_text(filename, values);

		if (new_file_name != filename)
		{
			Templi::rename(
				file, (file_path.parent_path() / std::filesystem::path(new_file_name)).c_str());
			std::cout << "[Rename] " << file << " -> "
					  << (file_path.parent_path() / std::filesystem::path(new_file_name))
					  << std::endl;
		}
	}
}

void Templi::configure(std::string template_path, std::vector<std::string> ignored_path)
{
	TempliConfig templi_config;
	templi_config.m_excludes = ignored_path;
	templi_config.m_excludes.push_back(TEMPLI_CONFIG_NAME);

	std::vector<std::string> files = Templi::get_folder_files(template_path, ignored_path);
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
	Templi::execute_scripts(values, templi_config.m_after);
	Templi::delete_file(Templi::create_config_path(output_path));
}
