#pragma once

#include <Templi/json.hpp>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace Templi
{
	using json = nlohmann::json;
	using String = std::string;
	using VectorString = std::vector<String>;
	using MapString = std::map<String, String>;
	using SetString = std::set<String>;
}  // namespace Templi
