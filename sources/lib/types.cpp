#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>

using namespace Templi;

// key method
std::string Templi::Key::keytype_to_string(KeyType type)
{
	switch (type)
	{
		case KeyType::BOOLEAN: return "BOOLEAN";
		case KeyType::SELECT: return "SELECT";
		case KeyType::INPUT: return "INPUT";
		default:
			throw Templi::Exception(
				"Invalid key type, these are the valid values [ SELECT, INPUT, BOOLEAN ]");
	}
};

KeyType Templi::Key::keytype_value_of(std::string type)
{
	if (type == "SELECT")
		return KeyType::SELECT;
	if (type == "BOOLEAN")
		return KeyType::BOOLEAN;
	if (type == "INPUT")
		return KeyType::INPUT;
	throw Templi::Exception(
		"Invalid key type, these are the valid values [ SELECT, INPUT, BOOLEAN ]");
};
