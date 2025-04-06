#pragma once

#include <Templi/types.hpp>
#include <map>

namespace Templi
{
	void generate(std::string template_path,
		std::string output_path,
		std::map<std::string, std::string> values,
		std::vector<std::string> ignored_path = {});

	void generate_with_templi_config(std::string template_path,
		std::string output_path,
		std::string path_suffix = "");

	void configure(std::string template_path, std::vector<std::string> ignored_path = {});

	class TempliConfig
	{
	public:
		std::vector<std::string> m_excludes{}, m_before{}, m_after{};
		std::vector<Key> m_keys{};

		void read(std::string template_path);
		void save(std::string template_path);

		TempliConfig() = default;
		TempliConfig(std::string template_path);
	};	// TempliConfig

}  // namespace Templi
