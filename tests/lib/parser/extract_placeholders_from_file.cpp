#include <gtest/gtest.h>

#include <set>

#include "../../utils.hpp"
#include "parser.hpp"

using namespace Templi;

TEST(Parser_extract_placeholders_from_file, basic_test)
{
	std::string file_path = FIXTURE("parser", "extract_placeholders_from_file_fixture.txt");

	std::set<std::string> expected = { "name", "place", "date" };

	std::set<std::string> result = Templi::extract_placeholders_from_file(file_path);

	ASSERT_EQ(result, expected);
}
