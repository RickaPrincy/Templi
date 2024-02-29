#pragma once

#include <Templi/json.hpp>
#include <map>
#include <set>
#include <string>
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
		TempliException(String message) : _message(message)
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
		String _key /*key_value*/ {}, _label{}, _default;
		KeyType _type;
		VectorString _choices{};
		bool _required{ false }, _clean{ true };

		Key(){};

		static KeyType keytype_value_of(String type);
		static String keytype_to_string(KeyType type);
	};	// Key

	class JSONConfig
	{
	public:
		VectorString _ignored_paths{};
		std::vector<Key> _keys{};

		void read_config(String template_path);
		void save_config(String template_path);

		JSONConfig(){};
		JSONConfig(String template_path){};
	};	// JSONConfig

}  // namespace Templi
