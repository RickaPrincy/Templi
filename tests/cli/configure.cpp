#include <gtest/gtest.h>

#include <Templi/Templi.hpp>
#include <Templi/types.hpp>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>

#include "../utils.hpp"
#include "utils.hpp"

using namespace Templi;

TEST(TempliCli_configure, fixtures)
{
	std::string template_path = FIXTURE("", "configure_template");
	std::string configure_command = get_templi_cli_path() + " configure -t " + template_path;
	std::string generated_config_path = Templi::create_config_path(template_path);

	std::system(configure_command.c_str());

	TempliConfig generated_config(template_path);
	std::vector<std::string> expected_keys_names = {
		"ANOTHER", "AUTHOR", "DESCRIPTION", "EMAIL", "GIT_URL", "PROJECT_NAME", "VERSION"
	};
	std::vector<std::string> expected_excludes_paths = { "templi.json", "ignored/ignored.txt" };

	ASSERT_EQ(generated_config.m_keys.size(), expected_keys_names.size());
	ASSERT_EQ(generated_config.m_excludes.size(), expected_excludes_paths.size());

	for (size_t i = 0; i < generated_config.m_excludes.size(); i++)
	{
		ASSERT_EQ(generated_config.m_excludes[i], expected_excludes_paths[i]);
	}

	for (size_t i = 0; i < generated_config.m_keys.size(); i++)
	{
		ASSERT_EQ(generated_config.m_keys[i].m_name, expected_keys_names[i]);
		ASSERT_EQ(generated_config.m_keys[i].m_type, KeyType::INPUT);
	}
	std::filesystem::remove(generated_config_path);
}
