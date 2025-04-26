#pragma once

#include <string>
#include <vector>

#define TEMPLI_CONFIG_NAME "templi.json"

namespace Templi
{
	class Exception : public std::exception
	{
	private:
		std::string m_message;

	public:
		Exception(std::string message) : m_message(message)
		{
		}
		const char* what() const noexcept override
		{
			return m_message.c_str();
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
		std::string m_name{}, m_label{}, m_default{};
		KeyType m_type;
		std::vector<std::string> m_choices{};
		bool m_required{ false }, m_clean{ true };

		Key() = default;

		static KeyType keytype_value_of(std::string type);
		static std::string keytype_to_string(KeyType type);
	};	// Key

}  // namespace Templi
