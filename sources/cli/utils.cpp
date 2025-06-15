#include "utils.hpp"

#include <algorithm>
#include <chrono>
#include <cpp_inquirer/cpp_inquirer.hpp>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <rcli/command.hpp>
#include <sstream>
#include <utility>

namespace Templi
{
	const std::map<std::string, std::shared_ptr<cpp_inquirer::validator>> BUILTIN_VALIDATORS = {
		{ "required", cpp_inquirer::validator_factory::required() },
		{ "optional", cpp_inquirer::validator_factory::optional() },
		{ "email", cpp_inquirer::validator_factory::email() },
		{ "number", cpp_inquirer::validator_factory::number() },
		{ "lowercase", cpp_inquirer::validator_factory::lowercase() },
		{ "uppercase", cpp_inquirer::validator_factory::uppercase() },
		{ "floating", cpp_inquirer::validator_factory::floating() },
	};

	static auto get_validator(const std::pair<std::string, std::string> &validator)
		-> std::shared_ptr<cpp_inquirer::validator>
	{
		const auto it = std::find_if(BUILTIN_VALIDATORS.begin(),
			BUILTIN_VALIDATORS.end(),
			[validator](const std::pair<std::string, std::shared_ptr<cpp_inquirer::validator>>
					&builtin_validtor) { return builtin_validtor.first == validator.first; });

		if (it != BUILTIN_VALIDATORS.end())
		{
			return it->second;
		}

		return cpp_inquirer::validator_factory::make(validator.first, validator.second);
	}

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

		std::vector<std::shared_ptr<cpp_inquirer::validator>> validators{};
		validators.reserve(placeholder.m_validators.size());
		for (const auto &validator : placeholder.m_validators)
		{
			validators.push_back(get_validator(validator));
		}
		return cpp_inquirer::text_question::prompt(copied_placeholder, validators);
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
