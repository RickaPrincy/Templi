#include <gtest/gtest.h>

#include <Templi/Templi.hpp>
#include <Templi/types.hpp>
#include <map>
#include <string>
#include <vector>

#include "../utils.hpp"
#include "fs_utils.hpp"
#include "utils.hpp"

using namespace Templi;

TEST(TempliLib_generate_with_args, fixtures)
{
	std::string template_path = FIXTURE("", "generate_template");
	std::string output_path = "generate_with_args_output";
	std::vector<std::string> ignored_path = {
		"ignored", "ignored.txt", "subfolder/subfolder/ignored.txt"
	};
	std::map<std::string, std::string> values = { { "ANOTHER", "another" },
		{ "ANOTHER_FILE", "another_file" },
		{ "AUTHOR", "author" },
		{ "DESCRIPTION", "description" },
		{ "EMAIL", "email" },
		{ "FILE", "file" },
		{ "GIT_URL", "git_url" },
		{ "PROJECT_NAME", "project_name" },
		{ "VERSION", "version" } };

	Templi::generate(template_path, output_path, values, ignored_path);

	Templi::delete_file(Templi::create_config_path(output_path));

	ASSERT_EQ_DIRECTORY(FIXTURE("", "generate_expected_output"), output_path);
}
