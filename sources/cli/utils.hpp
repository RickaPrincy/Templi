#pragma once

#include <Templi/types.hpp>
#include <rcli/command.hpp>
#include <string>

namespace Templi
{
	std::string generate_unique_id();
	std::string clone_template(std::string template_path);
	std::string ask_input_value(const Templi::Key &key);
	std::string to_slug(std::string input);
	std::string get_placeholder_value(rcli::Command *command, Templi::Key &key);
}  // namespace Templi
