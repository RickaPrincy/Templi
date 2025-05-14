#pragma once

#include <Templi/types.hpp>
#include <rcli/command.hpp>
#include <string>

namespace Templi
{
	std::string generate_unique_id();
	std::string clone_template(std::string template_path);
	std::string ask_input_value(const Templi::Placeholder &placeholder);
	std::string get_placeholder_value(rcli::Command *command, Templi::Placeholder &placeholder);
}  // namespace Templi
