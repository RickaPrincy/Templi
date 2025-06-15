#include "utils.hpp"

#include <chrono>
#include <cpp_inquirer/cpp_inquirer.hpp>
#include <filesystem>
#include <iostream>
#include <random>
#include <rcli/command.hpp>
#include <sstream>
#include <utility>

namespace Templi
{
	auto generate_unique_id() -> std::string
	{
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937_64 generator(seed);

		std::uniform_int_distribution<uint64_t> distribution;
		uint64_t randomValue = distribution(generator);
		std::stringstream ss;
		ss << std::hex << randomValue;
		return ss.str();
	}

	auto clone_template(const std::string &template_path) -> std::string
	{
		std::filesystem::path os_temp_path = std::filesystem::temp_directory_path();
		const std::filesystem::path template_temp_path =
			os_temp_path / std::filesystem::path(Templi::generate_unique_id());
		const std::string clone_command =
			"git clone " + template_path + " " + template_temp_path.string();

		std::cout << "Cloning the template to " + template_path + " ..." << "\n";
		std::system(clone_command.c_str());
		return template_temp_path.string();
	}

	auto ask_input_value(const Placeholder &placeholder) -> std::string
	{
		const auto copied_placeholder = placeholder.m_label;
		if (placeholder.m_type == PlaceholderType::SELECT)
		{
			return cpp_inquirer::select_question::prompt(
				copied_placeholder, vector_to_pair(placeholder.m_choices));
		}

		if (placeholder.m_type == PlaceholderType::BOOLEAN)
		{
			return cpp_inquirer::boolean_question::prompt(copied_placeholder);
		}

		return cpp_inquirer::text_question::prompt(copied_placeholder);
	}

	auto get_placeholder_value(rcli::command *command, const Templi::Placeholder &placeholder)
		-> std::string
	{
		auto option_value = command->get_option_value(placeholder.m_name);
		if (option_value.empty())
		{
			return Templi::ask_input_value(placeholder);
		}
		return option_value;
	}

	auto vector_to_pair(const std::vector<std::string> &vec)
		-> std::vector<std::pair<std::string, std::string>>
	{
		std::vector<std::pair<std::string, std::string>> result;
		result.reserve(vec.size());

		for (const auto &value : vec)
		{
			result.emplace_back(value, value);
		}
		return result;
	}
}  // namespace Templi
