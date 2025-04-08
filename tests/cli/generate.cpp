#include <gtest/gtest.h>

#include <Templi/Templi.hpp>
#include <Templi/types.hpp>
#include <cstdio>
#include <stdexcept>
#include <string>

#include "../utils.hpp"

using namespace Templi;

TEST(TempliCli_generate, fixtures)
{
	std::string template_path = FIXTURE("", "generate_template");
	std::string output_path = "generate_cli_output";
	auto templi_generate_command =
		get_templi_cli_path() + " generate -t " + template_path + " -o " + output_path;

	FILE* templi_cli = popen(templi_generate_command.c_str(), "w");
	if (!templi_cli)
	{
		throw std::runtime_error("Cannot run templi_cli");
	}

	std::vector<std::string> values = {
		"another", "author", "description", "email", "git_url", "project_name", "version"
	};

	for (const auto& value : values)
	{
		fprintf(templi_cli, "%s\n", value.c_str());
		fflush(templi_cli);
		sleep(1);
	}
	pclose(templi_cli);
	ASSERT_EQ_DIRECTORY(FIXTURE("", "generate_expected_output"), output_path);
}
