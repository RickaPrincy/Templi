#pragma once

#include <Templi/types.hpp>
#include <rcli/command.hpp>
#include <string>
#include <vector>

namespace Templi
{
	auto generate_unique_id() -> std::string;
	auto clone_template(const std::string &template_path) -> std::string;
	auto ask_input_value(const Templi::Placeholder &placeholder) -> std::string;

	auto get_placeholder_value(rcli::command *command, const Templi::Placeholder &placeholder)
		-> std::string;

	auto vector_to_pair(const std::vector<std::string> &vec)
		-> std::vector<std::pair<std::string, std::string>>;
}  // namespace Templi
