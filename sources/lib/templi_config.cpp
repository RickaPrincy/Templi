#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <fstream>

#include "fs_utils.hpp"
#include "utils.hpp"

using json = nlohmann::json;

namespace Templi
{
	TempliConfig::TempliConfig(const std::string &template_path)
	{
		this->read(template_path);
	}

	auto TempliConfig::read(const std::string &template_path) -> void
	{
		const std::string config_full_path = create_config_path(template_path);
		std::ifstream config_file(config_full_path);
		json config_json;

		if (!config_file.is_open())
		{
			throw Exception("Cannot open " + config_full_path);
		}

		try
		{
			config_file >> config_json;
			config_file.close();
		}
		catch (const json::parse_error &e)
		{
			throw Exception(config_full_path + " is not a valid json file");
		}

		try
		{
			m_excludes = config_json["excludes"];
			if (config_json["scripts"].is_object())
			{
				json scripts = config_json["scripts"];

				if (scripts["before"].is_array())
				{
					m_before = scripts["before"];
				}

				if (scripts["after"].is_array())
				{
					m_after = scripts["after"];
				}
			}

			for (auto placeholder : config_json["placeholders"])
			{
				Placeholder new_placeholder;
				new_placeholder.m_name = placeholder["name"];
				new_placeholder.m_label = placeholder["label"];
				new_placeholder.m_type = Placeholder::placeholdertype_value_of(placeholder["type"]);

				if (new_placeholder.m_type == PlaceholderType::SELECT)
				{
					new_placeholder.m_choices = placeholder["choices"];
				}

				this->m_placeholders.push_back(new_placeholder);
			}
		}
		catch (const json::exception &error)
		{
			throw Exception(config_full_path +
							" is not a valid config file (ref: "
							"https://github.com/RickaPrincy/Templi/blob/main/templi.json.md)");
		}
	}

	auto TempliConfig::save(const std::string &template_path) -> void
	{
		const std::string config_full_path = create_config_path(template_path);
		json new_config_json = json::object();
		json placeholders_json = json::array();

		new_config_json["excludes"] = m_excludes;

		if (!m_before.empty() || !m_after.empty())
		{
			json scripts = json::object();
			scripts["before"] = m_before;
			scripts["after"] = m_before;
			new_config_json["scripts"] = scripts;
		}

		for (auto placeholder : this->m_placeholders)
		{
			json new_placeholder = json::object();
			new_placeholder["name"] = placeholder.m_name;
			new_placeholder["label"] = placeholder.m_label;
			new_placeholder["type"] = Placeholder::placeholdertype_to_string(placeholder.m_type);

			if (placeholder.m_type == PlaceholderType::SELECT)
			{
				new_placeholder["choices"] = placeholder.m_choices;
			}
			placeholders_json.push_back(new_placeholder);
		}
		new_config_json["placeholders"] = placeholders_json;

		save_file(config_full_path, new_config_json);
	};
}  // namespace Templi
