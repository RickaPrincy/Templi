#include "read_config.hpp"

#include <TColor/TColor.hpp>
#include <Templi/TempliConfig.hpp>
#include <fstream>
#include <rcli/input_config.hpp>
#include <rcli/inputs.hpp>
#include <utility>

#include "Templi/types.hpp"

using namespace Templi;

static json get_templi_json(String config_path)
{
	std::ifstream config_file(config_path + TEMPLI_SEPARATOR + "templi.json");
	json config_json;

	if (!config_file.is_open())
	{
        TColor::write_endl(TColor::B_RED, "[ ERROR ]: \"templi.json\" was not found");
		exit(EXIT_FAILURE);
	}

	try
	{
		config_file >> config_json;
		config_file.close();
	}
	catch (const json::parse_error &e)
	{
		TColor::write_endl(TColor::B_RED, "[ ERROR ]: \"templi.json\" is not a valid json");
		config_file.close();
		std::exit(EXIT_FAILURE);
	}
	return config_json;
}

static String ask_input_value(json key)
{
	rcli::InputConfig config;

	if (key["type"].is_array())
	{
		return rcli::ask_value_in_list_as_number(key["label"], key["type"]);
	}

	if (key["type"] == "boolean")
	{
		bool default_value = true;
		if (key["default"].is_boolean())
			default_value = key["default"];

		return rcli::ask_boolean(key["label"], default_value) ? "true" : "false";
	}

	config.text(key["label"]);
	if (key["required"].is_boolean())
		config.required(key["required"]);

	if (key["default"].is_string())
		config.default_value(key["default"]);

	if (key["clean"].is_boolean())
		config.default_value(key["clean"]);

	return rcli::ask_input_value(config);
}

void Templi::ask_and_get_templi_config_value(String template_path,
	MapString &values,
	VectorString &ignored_paths)
{
	json config_content = get_templi_json(template_path);
	ignored_paths = config_content["ignored_paths"];

	for (const auto &key : config_content["keys"])
	{
		values.insert(std::make_pair(key["key"], ask_input_value(key)));
	}
}
