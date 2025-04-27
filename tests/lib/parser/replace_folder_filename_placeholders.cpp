#include <gtest/gtest.h>

#include <Templi/types.hpp>
#include <map>
#include <string>
#include <vector>

#include "../../utils.hpp"
#include "parser.hpp"

using namespace Templi;

TEST(TempliLib_replace_folder_filename_placeholders, fixtures)
{
	std::string template_path = FIXTURE("", "replace_folder_filename_placeholders");
	std::vector<std::string> ignored_path = { "folder1/{{IGNORED}}.txt", "folder2/{{IGNORED}}" };

	std::map<std::string, std::string> values = {
		{ "SUBFOLDER", "subfolder" }, { "ANOTHER_FILE", "another_file" }, { "FILE", "file" }
	};

	Templi::replace_folder_filename_placeholders(template_path, values, ignored_path);

	ASSERT_EQ_DIRECTORY(
		FIXTURE("", "replace_folder_filename_placeholders_expected_output"), template_path);
}
