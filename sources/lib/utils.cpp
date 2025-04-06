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

std::string Templi::ask_input_value(const Key &key)
{
	rcli::InputConfig config;

	if (key.m_type == KeyType::SELECT)
		return rcli::ask_value_in_list_as_number(key.m_label, key.m_choices);

	if (key.m_type == KeyType::BOOLEAN)
		return rcli::ask_boolean(key.m_label, key.m_default == "true") ? "true" : "false";

	config.text(key.m_label)
		.default_value(key.m_default)
		.required(key.m_required)
		.clean(key.m_clean);

	return rcli::ask_input_value(config);
}

void Templi::ask_and_get_templi_config_value(std::string template_path,
	std::map<std::string, std::string> &values,
	std::vector<std::string> &ignored_paths,
	std::vector<std::string> &before_generating,
	std::vector<std::string> &after_generating)
{
	TempliConfig templi_config(template_path);
	ignored_paths = templi_config.m_excludes;
	before_generating = templi_config.m_before;
	after_generating = templi_config.m_after;

	for (const auto &key : templi_config.m_keys)
		values.insert(std::make_pair(key.m_name, ask_input_value(key)));
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
