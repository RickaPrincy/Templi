#pragma once

#include <Templi/types.hpp>
#include <map>
#include <string>
#include <vector>

namespace Templi
{
	std::string create_config_path(std::string template_path);

	void execute_scripts(const std::map<std::string, std::string> &values,
		const std::vector<std::string> &scripts);

	void clone_template(std::string &template_path);
}  // namespace Templi
