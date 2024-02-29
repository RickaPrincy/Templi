#pragma once

#include <Templi/json.hpp>
#include <map>
#include <set>
#include <string>
#include <variant>
#include <vector>

#define TEMPLI_CONFIG_NAME "templi.json"

namespace Templi
{
	using json = nlohmann::json;
	using String = std::string;
	using VectorString = std::vector<String>;
	using MapString = std::map<String, String>;
	using SetString = std::set<String>;

	class TempliException : public std::exception
	{
	private:
		String _message;

	public:
		TempliException(const char* message) : _message(message)
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
		String _key /*key_value*/ {}, label{};
		KeyType _type;
		VectorString _choice{};
		bool _required{ false }, _clean{ true };
		std::variant<bool, String> _default;

		Key(){};
	};	// Key

	class JSONConfig
	{
	public:
		VectorString ignored_paths{};
		std::vector<Key> _keys{};
		
        void read_config(String template_path);
		void save_config(String template_path);

		JSONConfig(){};
		JSONConfig(String template_path){};
	};	// JSONConfig

}  // namespace Templi
