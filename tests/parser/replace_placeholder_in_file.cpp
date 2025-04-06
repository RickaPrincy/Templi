#include <gtest/gtest.h>

#include <fstream>
#include <map>
#include <sstream>

#include "parser.hpp"

using namespace Templi;

TEST(Parser_replace_placeholders_in_file, basic_test)
{
	// Create a mock input file with placeholder content
	std::string input_file = "test_input.txt";
	std::ofstream input_stream(input_file);
	input_stream << "Hello {{name}}, welcome to {{place}}!\n";
	input_stream << "Your appointment is on {{date}}.\n";
	input_stream << "Bye {{name}}.\n";  // This line should also be included in the expected output
	input_stream.close();

	// Create a temporary output file path
	std::string output_file = "test_output.txt";

	// Set the values for placeholders
	std::map<std::string, std::string> values = {
		{ "name", "Alice" },
		{ "place", "Wonderland" },
		{ "date", "2025-05-01" }
	};

	// Act: Replace placeholders and save to the output file
	Templi::replace_placeholders_in_file(input_file, output_file, values);

	// Read the output file and check the content
	std::ifstream output_stream(output_file);
	std::stringstream output_buffer;
	output_buffer << output_stream.rdbuf();
	std::string output_content = output_buffer.str();

	// Expected content after replacement
	std::string expected_content =
		"Hello Alice, welcome to Wonderland!\nYour appointment is on 2025-05-01.\nBye Alice.\n";  // Include the final line here

	// Assert: Check if the output content matches the expected result
	ASSERT_EQ(output_content, expected_content);

	// Clean up the temporary input and output files
	std::remove(input_file.c_str());
	std::remove(output_file.c_str());
}
