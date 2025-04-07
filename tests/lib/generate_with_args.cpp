#include <gtest/gtest.h>

#include <Templi/Templi.hpp>
#include <Templi/types.hpp>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "../utils.hpp"

using namespace Templi;

TEST(Configure_generate_with_args, fixtures)
{
	std::string template_path = FIXTURE("", "generate_template");
	std::string generated_config_path =
		(std::filesystem::path(template_path) / std::filesystem::path(TEMPLI_CONFIG_NAME)).string();
	std::string output_path = "generate_with_args_output";
	std::vector<std::string> ignored_path = {
		"ignored", "ignored.txt", "subfolder/subfolder/ignored.txt"
	};
	std::map<std::string, std::string> values = { { "ANOTHER", "another" },
		{ "AUTHOR", "author" },
		{ "DESCRIPTION", "description" },
		{ "EMAIL", "email" },
		{ "GIT_URL", "git_url" },
		{ "PROJECT_NAME", "project_name" },
		{ "VERSION", "version" } };

	Templi::generate(template_path, output_path, values, ignored_path);

	ASSERT_EQ_DIRECTORY(FIXTURE("", "generate_expected_output"), output_path);
}
