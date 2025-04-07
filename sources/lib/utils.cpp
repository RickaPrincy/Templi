#include "utils.hpp"

#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <random>
#include <rcli/input_config.hpp>
#include <rcli/inputs.hpp>
#include <sstream>

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

static std::string generate_unique_id()
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937_64 generator(seed);

	std::uniform_int_distribution<uint64_t> distribution;
	uint64_t randomValue = distribution(generator);
	std::stringstream ss;
	ss << std::hex << randomValue;
	return ss.str();
}

void Templi::clone_template(std::string &template_path)
{
	std::filesystem::path os_temp_path = std::filesystem::temp_directory_path();
	const std::filesystem::path template_temp_path =
		os_temp_path / std::filesystem::path(generate_unique_id());
	const std::string clone_command =
		"git clone " + template_path + " " + template_temp_path.string();

	template_path = template_temp_path.string();

	TColor::write_endl(
		TColor::B_GREEN, std::string("Cloning the template to " + template_path + " ..."));
	std::system(clone_command.c_str());
}
