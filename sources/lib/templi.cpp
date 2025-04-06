#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>

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
	std::vector<std::string> files = Templi::get_folder_files(template_path, ignored_path);

	if (files.empty())
		throw Templi::Exception("Folder empty or no words inside {{}} was found");

	Templi::copy_folder(template_path, output_path);
	Templi::delete_file(Templi::create_config_path(output_path));

	for (auto file : files)
	{
		auto path = output_path + file.substr(template_path.size());
		Templi::replace_placeholders_in_file(file, path, values);
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
		std::set<std::string> words_found = Templi::extract_placeholders_from_file(file);

		if (words_found.empty())
			templi_config.m_excludes.push_back(file.substr(template_path.size() + 1));

		for (auto word_found : words_found)
			words.insert(word_found);
	}

	for (auto word : words)
	{
		Key new_key;
		new_key.m_name = word;
		new_key.m_type = KeyType::INPUT;
		templi_config.m_keys.push_back(new_key);
	}
	templi_config.save(template_path);
}

void Templi::generate_with_templi_config(std::string template_path,
	std::string output_path,
	std::string path_suffix)
{
	std::map<std::string, std::string> values{ { "TEMPLI_OUTPUT_FOLDER", output_path } };
	std::vector<std::string> ignored_paths{}, before_generating{}, after_generating{};
	bool is_github_repository = false;

	if (template_path.length() >= GIT_SUFFIX.length())
	{
		// test if the template_path is a git repository
		if (0 == template_path.compare(
					 template_path.length() - GIT_SUFFIX.length(), GIT_SUFFIX.length(), GIT_SUFFIX))
		{
			Templi::clone_template(template_path);
			is_github_repository = true;
		}
	}
	std::string templi_template_path = template_path + path_suffix;

	try
	{
		Templi::ask_and_get_templi_config_value(
			templi_template_path, values, ignored_paths, before_generating, after_generating);
		Templi::execute_scripts(values, before_generating);
		Templi::generate(templi_template_path, output_path, values, ignored_paths);
		Templi::execute_scripts(values, after_generating);
	}
	catch (Templi::Exception error)
	{
		if (is_github_repository)
		{
			Templi::delete_folder(template_path);
		}
		std::string message = error.what();
		throw Templi::Exception(message);
	}

	if (is_github_repository)
	{
		Templi::delete_folder(template_path);
	}
}
