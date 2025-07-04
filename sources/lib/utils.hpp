#pragma once

#include <Templi/types.hpp>
#include <map>
#include <string>
#include <vector>

namespace Templi
{
	auto create_config_path(const std::string &template_path) -> std::string;

	auto execute_scripts(const std::map<std::string, std::string> &values,
		const std::vector<std::string> &scripts) -> void;
}  // namespace Templi
