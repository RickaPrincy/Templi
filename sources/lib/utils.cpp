#include "utils.hpp"

#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <cstdlib>
#include <filesystem>
#include <rcli/input_config.hpp>
#include <rcli/inputs.hpp>

#include "parser.hpp"

using namespace Templi;

std::string Templi::create_config_path(std::string template_path)
{
	return (std::filesystem::path(template_path) / std::filesystem::path(TEMPLI_CONFIG_NAME))
		.string();
}

void Templi::execute_scripts(const std::map<std::string, std::string> &values,
	const std::vector<std::string> &scripts)
{
	for (const auto script : scripts)
	{
		std::string command = Templi::replace_placeholders_in_text(script, values);
		TColor::write_endl(TColor::B_WHITE, command);
		std::system(command.c_str());
	}
}
