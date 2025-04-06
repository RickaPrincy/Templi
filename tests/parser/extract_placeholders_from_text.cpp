
#include <gtest/gtest.h>

#include "parser.hpp"

using namespace Templi;

TEST(Parser_extract_placeholder_from_text, no_placeholder)
{
	// Arrange
	std::string text = "I have no placeholders";
	std::set<std::string> expected = {};

	// Act
	std::set<std::string> actual = Templi::extract_placeholders_from_text(text);

	// Assert
	ASSERT_EQ(expected, actual);
}

TEST(Parser_extract_placeholder_from_text, one_placeholder)
{
	// Arrange
	std::string text = "I have {{one}} placeholder";
	std::set<std::string> expected = { "one" };

	// Act
	std::set<std::string> actual = Templi::extract_placeholders_from_text(text);

	// Assert
	ASSERT_EQ(expected, actual);
}

TEST(Parser_extract_placeholder_from_text, multiple_placeholders)
{
	// Arrange
	std::string text = "Here are {{one}}, {{two}}, and {{three}} placeholders";
	std::set<std::string> expected = { "one", "two", "three" };

	// Act
	std::set<std::string> actual = Templi::extract_placeholders_from_text(text);

	// Assert
	ASSERT_EQ(expected, actual);
}

TEST(Parser_extract_placeholder_from_text, nested_placeholders)
{
	// Arrange
	std::string text = "Nested {{one{{inner}}}} placeholder";
	std::set<std::string> expected = {
		"one{{inner"
	};	// considering how your function handles nested placeholders.

	// Act
	std::set<std::string> actual = Templi::extract_placeholders_from_text(text);

	// Assert
	ASSERT_EQ(expected, actual);
}

TEST(Parser_extract_placeholder_from_text, escaped_brackets)
{
	// Arrange
	std::string text = "Escaped \\{{escaped}} and {{one}}";
	std::set<std::string> expected = { "one" };

	// Act
	std::set<std::string> actual = Templi::extract_placeholders_from_text(text);

	// Assert
	ASSERT_EQ(expected, actual);
}
