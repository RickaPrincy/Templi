#include <gtest/gtest.h>

#include "parser.hpp"

using namespace Templi;

TEST(Parser_replace_placeholder_in_text, no_word)
{
	// Arrange
	std::map<std::string, std::string> values = {};
	std::string text = "I have no value";
	
	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);
	
	// Assert
	ASSERT_EQ(actual, text);
}

TEST(Parser_replace_placeholder_in_text, one_word)
{
	// Arrange
	std::map<std::string, std::string> values = { { "one", "cool" } };
	std::string text = "I have {{one}} value";
	std::string expected = "I have cool value";

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}

TEST(Parser_replace_placeholder_in_text, one_word_at_end)
{
	// Arrange
	std::map<std::string, std::string> values = { { "one", "cool" } };
	std::string text = "I have {{one}}";
	std::string expected = "I have cool";

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}

TEST(Parser_replace_placeholder_in_text, one_word_at_begin)
{
	// Arrange
	std::map<std::string, std::string> values = { { "je", "cool" } };
	std::string text = "{{je}} I have";
	std::string expected = "cool I have";

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}

TEST(Parser_replace_placeholder_in_text, one_word_only)
{
	// Arrange
	std::map<std::string, std::string> values = { { "je", "cool" } };
	std::string text = "{{je}}";
	std::string expected = "cool";

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}

TEST(Parser_replace_placeholder_in_text, two_words)
{
	// Arrange
	std::map<std::string, std::string> values = { { "je", "cool" }, { "happy", "noo" } };
	std::string text = "{{je}} je ricka princy {{happy}} lorem";
	std::string expected = "cool je ricka princy noo lorem";

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}

TEST(Parser_replace_placeholder_in_text, many_words)
{
	// Arrange
	std::string text = "je{{cool}} I'm happy{{lol}},!no\\ motion {{number1}}, things, {{nice}}";
	std::string expected = "jeje I'm happylolo,!no\\ motion {{number1}}, things, nice";
	std::map<std::string, std::string> values = {
		{ "cool", "je" }, { "lol", "lolo" }, { "nice", "nice" }
	};

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}

TEST(Parser_replace_placeholder_in_text, with_no_close)
{
	// Arrange
	std::string text = "je{{cool{{nice}}, {{je";
	std::string expected = "jeVALUE, {{je";
	std::map<std::string, std::string> values = { { "cool{{nice", "VALUE" } };

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}

TEST(Parser_replace_placeholder_in_text, with_escaped_bracket)
{
	// Arrange
	std::string text = "je\\{{escaped{{input}}";
	std::string expected = "je{{escapedvalue";
	std::map<std::string, std::string> values = { { "input", "value" } };

	// Act
	std::string actual = Templi::replace_placeholders_in_text(text, values);

	// Assert
	ASSERT_EQ(actual, expected);
}
