#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>

#include "fs_utils.hpp"
#include "parser.hpp"
#include "utils.hpp"

using namespace Templi;

void Templi::generate(String template_path,
	String output_path,
	MapString values,
	VectorString ignored_path)
{
	VectorString files;
	get_folder_files(template_path, files, ignored_path);

	if (files.empty())
		throw Templi::Exception("Folder empty or no words inside {{}} was found");

	if (!copy_folder(template_path, output_path) ||
		!delete_file(Templi::create_config_path(output_path)))
	{
		throw Templi::Exception("Error when try to copy the templates");
	}

	for (auto file : files)
	{
		auto path = output_path + file.substr(template_path.size());
		file_brackets_parser(file, path, values);
	}
}

void Templi::configure(String template_path, VectorString ignored_path)
{
	VectorString files;
	SetString words;
	JSONConfig json_config;

	json_config._ignored_paths = ignored_path;
	json_config._ignored_paths.push_back(TEMPLI_CONFIG_NAME);

	get_folder_files(template_path, files, ignored_path);

	if (files.empty())
		throw Templi::Exception("Folder empty or no words inside {{}} was found");

	for (auto file : files)
	{
		SetString words_found = file_get_brackets_words(file);

		if (words_found.empty())
			json_config._ignored_paths.push_back(file.substr(template_path.size() + 1));

		for (auto word_found : words_found)
			words.insert(word_found);
	}

	for (auto word : words)
	{
		Key new_key;
		new_key._key = word;
		json_config._keys.push_back(new_key);
	}
	json_config.save_config(Templi::create_config_path(template_path));
}

void Templi::generate_with_templi_config(String template_path, String output_path)
{
	MapString values{};
	VectorString ignored_paths{};
	Templi::ask_and_get_templi_config_value(template_path, values, ignored_paths);
	Templi::generate(template_path, output_path, values, ignored_paths);
}
