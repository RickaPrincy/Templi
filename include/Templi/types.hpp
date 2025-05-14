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

	// all supported types of placeholder in the templi.json["placeholders"]
	enum class PlaceholderType
	{
		INPUT,
		BOOLEAN,
		SELECT
	};	// PlaceholderType

	class Placeholder
	{
	public:
		std::string m_name{}, m_label{}, m_default{};
		PlaceholderType m_type;
		std::vector<std::string> m_choices{};
		bool m_required{ true }, m_remove_spaces{ true };

		Placeholder() = default;

		static PlaceholderType placeholdertype_value_of(std::string type);
		static std::string placeholdertype_to_string(PlaceholderType type);
	};	// Placeholder

}  // namespace Templi
