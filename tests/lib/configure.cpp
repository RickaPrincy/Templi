#include <gtest/gtest.h>

#include <Templi/Templi.hpp>
#include <Templi/types.hpp>
#include <filesystem>
#include <string>

#include "../utils.hpp"
#include "utils.hpp"

using namespace Templi;

TEST(TempliLib_configure, fixtures)
{
	std::string template_path = FIXTURE("", "configure_template");
	std::string generated_config_path = Templi::create_config_path(template_path);

	Templi::configure(template_path);
	TempliConfig generated_config(template_path);
	std::vector<std::string> expected_placeholders_names = { "ANOTHER",
		"ANOTHER_FILE",
		"AUTHOR",
		"DESCRIPTION",
		"EMAIL",
		"FILE",
		"GIT_URL",
		"PROJECT_NAME",
		"VERSION" };
	std::vector<std::string> expected_excludes_paths = { "templi.json", "ignored/ignored.txt" };

	ASSERT_EQ(generated_config.m_placeholders.size(), expected_placeholders_names.size());
	ASSERT_EQ(generated_config.m_excludes.size(), expected_excludes_paths.size());

	for (size_t i = 0; i < generated_config.m_excludes.size(); i++)
	{
		ASSERT_EQ(generated_config.m_excludes[i], expected_excludes_paths[i]);
	}

	for (size_t i = 0; i < generated_config.m_placeholders.size(); i++)
	{
		auto name = generated_config.m_placeholders[i].m_name;
		ASSERT_EQ(name, expected_placeholders_names[i]);
		ASSERT_EQ(generated_config.m_placeholders[i].m_type, PlaceholderType::TEXT);
		ASSERT_EQ(generated_config.m_placeholders[i].m_label, name);
	}
	std::filesystem::remove(generated_config_path);
}
