#include "utils.hpp"

#include <TColor/TColor.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <rcli/input_config.hpp>
#include <rcli/inputs.hpp>

#include "Templi/Templi.hpp"

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
	VectorString &ignored_paths)
{
	JSONConfig json_config(template_path);
	ignored_paths = json_config._ignored_paths;

	for (const auto &key : json_config._keys)
	{
		values.insert(std::make_pair(key._key, ask_input_value(key)));
	}
}
