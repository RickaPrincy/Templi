#pragma once

#include <Templi/types.hpp>
#include <map>
#include <string>
#include <vector>

namespace Templi
{

	std::string ask_input_value(const Key &key);

	std::string create_config_path(std::string template_path);

	void ask_and_get_templi_config_value(std::string template_path,
		std::map<std::string, std::string> &values,
		std::vector<std::string> &ignored_paths,
		std::vector<std::string> &before_generating,
		std::vector<std::string> &after_generating);

	void execute_scripts(const std::map<std::string, std::string> &values,
		const std::vector<std::string> &scripts);

	void clone_template(std::string &template_path);
}  // namespace Templi
