#include <gtest/gtest.h>

#include <fstream>
#include <set>

#include "parser.hpp"

using namespace Templi;

TEST(Parser_extract_placeholders_from_file, basic_test)
{
	// Create a mock input file with placeholder content
	std::string input_file = "test_input.txt";
	std::ofstream input_stream(input_file);
	input_stream << "Hello {{name}}, welcome to {{place}}!\n";
	input_stream << "Your appointment is on {{date}}.\n";
	input_stream.close();

	// Expected result
	std::set<std::string> expected = { "name", "place", "date" };

	// Act: Call the function that processes the file
	std::set<std::string> result = Templi::extract_placeholders_from_file(input_file);

	// Assert: Check if the result matches the expected set
	ASSERT_EQ(result, expected);

	// Clean up the temporary input file
	std::remove(input_file.c_str());
}
