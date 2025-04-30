#pragma once

#include <Templi/types.hpp>
#include <string>

namespace Templi
{
	std::string generate_unique_id();
	std::string clone_template(std::string template_path);
	std::string ask_input_value(const Templi::Key &key);
}  // namespace Templi
