#include <gtest/gtest.h>

#include <set>

#include "../utils.hpp"
#include "parser.hpp"

using namespace Templi;

TEST(Parser_extract_placeholders_from_file, basic_test)
{
	std::string file_path = FIXTURE("parser", "extract_placeholders_from_file_fixture.txt");

	// Expected result
	std::set<std::string> expected = { "name", "place", "date" };

	// Act: Call the function that processes the file
	std::set<std::string> result = Templi::extract_placeholders_from_file(file_path);

	// Assert: Check if the result matches the expected set
	ASSERT_EQ(result, expected);
}
