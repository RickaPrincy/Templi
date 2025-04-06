#pragma once

#include <string>
#include <vector>

#define TEMPLI_CONFIG_NAME "templi.json"

namespace Templi
{
	class Exception : public std::exception
	{
	private:
		std::string _message;

	public:
		Exception(std::string message) : _message(message)
		{
		}
		const char* what() const noexcept override
		{
			return _message.c_str();
		}
	};	// TempliException

	// all supported types of key in the templi.json["keys"]
	enum class KeyType
	{
		INPUT,
		BOOLEAN,
		SELECT
	};	// KeyType

	class Key
	{
	public:
		std::string _key /*key_value*/ {}, _label{}, _default{};
		KeyType _type;
		std::vector<std::string> _choices{};
		bool _required{ false }, _clean{ true };

		Key() = default;

		static KeyType keytype_value_of(std::string type);
		static std::string keytype_to_string(KeyType type);
	};	// Key

}  // namespace Templi
