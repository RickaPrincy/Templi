#include "utils.hpp"

#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "parser.hpp"

namespace Templi
{
	auto create_config_path(const std::string &template_path) -> std::string
	{
		return (std::filesystem::path(template_path) / std::filesystem::path(TEMPLI_CONFIG_NAME))
			.string();
	}

	void execute_scripts(const std::map<std::string, std::string> &values,
		const std::vector<std::string> &scripts)
	{
		for (const auto &script : scripts)
		{
			std::string command = Templi::replace_placeholders_in_text(script, values);
			std::cout << command << "\n";
			std::system(command.c_str());
		}
	}
}  // namespace Templi
