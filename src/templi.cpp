#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>

#include "fs_utils.hpp"
#include "parser.hpp"
#include "read_config.hpp"

using namespace Templi;

bool Templi::generate(String template_path,
	String output_path,
	MapString values,
	VectorString ignored_path)
{
	VectorString files;
	get_folder_files(template_path, files, ignored_path);

	if (files.empty())
		return false;

	if (!copy_folder(template_path, output_path) ||
		!delete_file(output_path + TEMPLI_SEPARATOR + "templi.json"))
	{
		return false;
	}

	for (auto file : files)
	{
		auto path = output_path + file.substr(template_path.size());
		file_brackets_parser(file, path, values);
	}
	return true;
}

bool Templi::configure(String template_path, VectorString ignored_path)
{
	VectorString files;
	SetString words;
	get_folder_files(template_path, files, ignored_path);
	json config_content = { { "ignored_paths", ignored_path }, { "keys", json::array() } };
	config_content["ignored_paths"].push_back("templi.json");

	if (files.empty())
		return false;

	for (auto file : files)
	{
		SetString words_found = file_get_brackets_words(file);
		if (words_found.empty())
		{
			config_content["ignored_paths"].push_back(file.substr(template_path.size() + 1));
		}

		for (auto word_found : words_found)
		{
			words.insert(word_found);
		}
	}

	for (auto word : words)
	{
		json new_word = { { "key", word }, { "type", "input" }, { "label", "" } };
		config_content["keys"].push_back(new_word);
	}
	return save_file(template_path + TEMPLI_SEPARATOR + "templi.json", config_content);
}

bool Templi::generate_with_templi_config(String template_path, String output_path)
{
	MapString values{};
	VectorString ignored_paths{};
	try
	{
		Templi::ask_and_get_templi_config_value(template_path, values, ignored_paths);
		return Templi::generate(template_path, output_path, values, ignored_paths);
	}
	catch (json::exception error)
	{
		TColor::write_endl(TColor::B_RED,
			"[ ERROR ]: \"templi.json\" is not valid (ref: "
			"https://github.com/RickaPrincy/Templi)");
		return false;
	}
}
