#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>

using namespace Templi;

// placeholder method
std::string Templi::Placeholder::placeholdertype_to_string(PlaceholderType type)
{
	switch (type)
	{
		case PlaceholderType::BOOLEAN: return "BOOLEAN";
		case PlaceholderType::SELECT: return "SELECT";
		case PlaceholderType::INPUT: return "INPUT";
		default:
			throw Templi::Exception(
				"Invalid placeholder type, these are the valid values [ SELECT, INPUT, BOOLEAN ]");
	}
};

PlaceholderType Templi::Placeholder::placeholdertype_value_of(std::string type)
{
	if (type == "SELECT")
		return PlaceholderType::SELECT;
	if (type == "BOOLEAN")
		return PlaceholderType::BOOLEAN;
	if (type == "INPUT")
		return PlaceholderType::INPUT;
	throw Templi::Exception(
		"Invalid placeholder type, these are the valid values [ SELECT, INPUT, BOOLEAN ]");
};
