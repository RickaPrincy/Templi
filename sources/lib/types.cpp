#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>

namespace Templi
{
	// placeholder method
	auto Templi::Placeholder::placeholdertype_to_string(PlaceholderType type) -> std::string
	{
		switch (type)
		{
			case PlaceholderType::BOOLEAN: return "BOOLEAN";
			case PlaceholderType::SELECT: return "SELECT";
			case PlaceholderType::TEXT: return "TEXT";
			default:
				throw Templi::Exception(
					"Invalid placeholder type, these are the valid values [ SELECT, TEXT, BOOLEAN "
					"]");
		}
	};

	auto Templi::Placeholder::placeholdertype_value_of(const std::string &type) -> PlaceholderType
	{
		if (type == "SELECT")
			return PlaceholderType::SELECT;
		if (type == "BOOLEAN")
			return PlaceholderType::BOOLEAN;
		if (type == "TEXT")
			return PlaceholderType::TEXT;
		throw Templi::Exception(
			"Invalid placeholder type, these are the valid values [ SELECT, TEXT, BOOLEAN ]");
	};
}  // namespace Templi
