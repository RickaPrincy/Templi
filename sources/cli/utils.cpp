#include "utils.hpp"

#include <TColor/TColor.hpp>
#include <chrono>
#include <filesystem>
#include <random>
#include <rcli/input_config.hpp>
#include <rcli/inputs.hpp>
#include <sstream>

using namespace Templi;

/* Just some functions */
std::string Templi::generate_unique_id()
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937_64 generator(seed);

	std::uniform_int_distribution<uint64_t> distribution;
	uint64_t randomValue = distribution(generator);
	std::stringstream ss;
	ss << std::hex << randomValue;
	return ss.str();
}

std::string Templi::clone_template(std::string template_path)
{
	std::filesystem::path os_temp_path = std::filesystem::temp_directory_path();
	const std::filesystem::path template_temp_path =
		os_temp_path / std::filesystem::path(Templi::generate_unique_id());
	const std::string clone_command =
		"git clone " + template_path + " " + template_temp_path.string();

	TColor::write_endl(
		TColor::B_GREEN, std::string("Cloning the template to " + template_path + " ..."));
	std::system(clone_command.c_str());
  return template_temp_path.string();

}

rcli::InputConfig config;
std::string Templi::ask_input_value(const Key &key)
{
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
