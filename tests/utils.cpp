#include "utils.hpp"

#include <filesystem>

std::string FIXTURE(std::string prefix, std::string file)
{
	return std::filesystem::path("fixtures") / std::filesystem::path(prefix) /
		   std::filesystem::path(file);
}
