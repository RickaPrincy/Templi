#include <gtest/gtest.h>

#include <Templi/Templi.hpp>
#include <Templi/types.hpp>
#include <map>
#include <string>

#include "../utils.hpp"

using namespace Templi;

TEST(TempliLib_generate_with_templi_config, fixtures)
{
	std::string template_path = FIXTURE("", "generate_template");
	std::string output_path = "generate_lib_with_templi_config_output";
	std::map<std::string, std::string> values = { { "ANOTHER", "another" },
		{ "ANOTHER_FILE", "another_file" },
		{ "AUTHOR", "author" },
		{ "DESCRIPTION", "description" },
		{ "EMAIL", "email" },
		{ "FILE", "file" },
		{ "GIT_URL", "git_url" },
		{ "PROJECT_NAME", "project_name" },
		{ "VERSION", "version" } };

	Templi::generate_with_templi_config(
		template_path, output_path, [&](Key key) { return values[key.m_name]; });

	ASSERT_EQ_DIRECTORY(FIXTURE("", "generate_expected_output"), output_path);
}
