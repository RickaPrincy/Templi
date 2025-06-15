#pragma once

#include <cstdint>
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
		Exception(std::string message) : m_message(std::move(message))
		{
		}

		[[nodiscard]] auto what() const noexcept -> const char* override
		{
			return m_message.c_str();
		}
	};	// TempliException

	enum class PlaceholderType : std::uint8_t
	{
		TEXT,
		SELECT,
		BOOLEAN
	};	// PlaceholderType

	class Placeholder
	{
	public:
		std::string m_name{}, m_label{};
		std::vector<std::string> m_choices{};
		PlaceholderType m_type{ PlaceholderType::TEXT };

		Placeholder() = default;

		static auto placeholdertype_value_of(const std::string& type) -> PlaceholderType;
		static auto placeholdertype_to_string(PlaceholderType type) -> std::string;
	};	// Placeholder
}  // namespace Templi
