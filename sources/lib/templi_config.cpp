#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <fstream>

#include "fs_utils.hpp"
#include "utils.hpp"

using namespace Templi;

using json = nlohmann::json;

Templi::TempliConfig::TempliConfig(std::string template_path)
{
	this->read(template_path);
}

void Templi::TempliConfig::read(std::string template_path)
{
	const std::string config_full_path = Templi::create_config_path(template_path);
	std::ifstream config_file(config_full_path);
	json config_json;

	if (!config_file.is_open())
		throw Templi::Exception("Cannot open " + config_full_path);

	try
	{
		config_file >> config_json;
		config_file.close();
	}
	catch (const json::parse_error &e)
	{
		throw Templi::Exception(config_full_path + " is not a valid json file");
	}

	try
	{
		m_excludes = config_json["excludes"];
		if (config_json["scripts"].is_object())
		{
			json scripts = config_json["scripts"];
			m_before = scripts["before"];
			m_after = scripts["after"];
		}

		for (auto key : config_json["keys"])
		{
			Key new_key;
			new_key.m_name = key["name"];
			new_key.m_label = key["label"];
			new_key.m_type = Key::keytype_value_of(key["type"]);

			if (new_key.m_type == KeyType::SELECT)
				new_key.m_choices = key["choices"];
			if (key["required"].is_boolean())
				new_key.m_required = key["required"];
			if (key["clean"].is_boolean())
				new_key.m_clean = key["clean"];
			if (key["default"].is_string() && !key["default"].empty())
				new_key.m_default = key["default"];
			this->m_keys.push_back(new_key);
		}
	}
	catch (const json::exception &error)
	{
		throw Templi::Exception(config_full_path +
								" is not a valid config file (ref: "
								"https://github.com/RickaPrincy/Templi/blob/main/templi.json.md)");
	}
}

void Templi::TempliConfig::save(std::string template_path)
{
	const std::string config_full_path = Templi::create_config_path(template_path);
	json new_config_json = json::object();
	json keys_json = json::array();

	new_config_json["excludes"] = m_excludes;

	if (!m_before.empty() || !m_after.empty())
	{
		json scripts = json::object();
		scripts["before"] = m_before;
		scripts["after"] = m_before;
		new_config_json["scripts"] = scripts;
	}

	for (auto key : m_keys)
	{
		json new_key = json::object();
		new_key["name"] = key.m_name;
		new_key["label"] = key.m_label;
		new_key["type"] = Key::keytype_to_string(key.m_type);

		if (key.m_required)
			new_key["required"] = key.m_required;
		if (!key.m_clean)
			new_key["clean"] = key.m_clean;
		if (key.m_type == KeyType::SELECT)
			new_key["choices"] = key.m_choices;
		if (!key.m_default.empty())
			new_key["default"] = key.m_default;
		keys_json.push_back(new_key);
	}
	new_config_json["keys"] = keys_json;

	Templi::save_file(config_full_path, new_config_json);
};
