#include <gtest/gtest.h>

#include <fstream>
#include <map>
#include <sstream>

#include "../utils.hpp"
#include "parser.hpp"

using namespace Templi;

TEST(Parser_replace_placeholders_in_file, basic_test)
{
	// Create a mock input file with placeholder content
	std::string input_file = FIXTURE("parser", "replace_placeholders_in_file_fixture.txt");

	// Create a temporary output file path
	std::string output_file = "test_output.txt";

	std::map<std::string, std::string> values = {
		{ "name", "Alice" }, { "place", "Wonderland" }, { "date", "2025-05-01" }
	};

	Templi::replace_placeholders_in_file(input_file, output_file, values);

	std::ifstream output_stream(output_file);
	std::stringstream output_buffer;
	output_buffer << output_stream.rdbuf();
	std::string output_content = output_buffer.str();

	std::string expected_content =
		"Hello Alice, welcome to Wonderland!\nYour appointment is on 2025-05-01.\nBye "
		"Alice.\n";	 // Include the final line here

	ASSERT_EQ(output_content, expected_content);

	std::remove(input_file.c_str());
	std::remove(output_file.c_str());
}
