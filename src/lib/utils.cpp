#include "utils.hpp"

#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <cstdlib>
#include <rcli/input_config.hpp>
#include <rcli/inputs.hpp>

#include "parser.hpp"

using namespace Templi;

String Templi::create_config_path(String template_path)
{
	return template_path + TEMPLI_SEPARATOR + TEMPLI_CONFIG_NAME;
}

String Templi::ask_input_value(const Key &key)
{
	rcli::InputConfig config;

	if (key._type == KeyType::SELECT)
		return rcli::ask_value_in_list_as_number(key._label, key._choices);

	if (key._type == KeyType::BOOLEAN)
		return rcli::ask_boolean(key._label, key._default == "true") ? "true" : "false";

	config.text(key._label).default_value(key._default).required(key._required).clean(key._clean);

	return rcli::ask_input_value(config);
}

void Templi::ask_and_get_templi_config_value(String template_path,
	MapString &values,
	VectorString &ignored_paths,
	VectorString &before_generating,
	VectorString &after_generating)
{
	JSONConfig json_config(template_path);
	ignored_paths = json_config._ignored_paths;
	before_generating = before_generating;
	after_generating = after_generating;

	for (const auto &key : json_config._keys)
		values.insert(std::make_pair(key._key, ask_input_value(key)));
}

void Templi::execute_scripts(const MapString &values, const VectorString &scripts)
{
	for (const auto script : scripts)
	{
		String command = Templi::replace_brackets_words(script, values);
		TColor::write(TColor::B_WHITE, command);
		std::system(script.c_str());
	}
}
