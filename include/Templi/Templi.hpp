#pragma once

#include <Templi/types.hpp>
#include <functional>
#include <map>

namespace Templi
{
	auto generate(const std::string &template_path,
		const std::string &output_path,
		const std::map<std::string, std::string> &values,
		const std::vector<std::string> &excludes = {}) -> void;

	auto generate_with_templi_config(const std::string &template_path,
		const std::string &output_path,
		std::function<std::string(Placeholder placeholder)> get_placeholder_value) -> void;

	auto configure(const std::string &template_path) -> void;

	class TempliConfig
	{
	public:
		std::vector<std::string> m_excludes{}, m_before{}, m_after{};
		std::vector<Placeholder> m_placeholders{};

		auto read(const std::string &template_path) -> void;
		auto save(const std::string &template_path) -> void;

		TempliConfig() = default;
		TempliConfig(const std::string &template_path);
	};	// TempliConfig

}  // namespace Templi
