#pragma once

#include <Templi/types.hpp>
#include <functional>
#include <vector>

#include "json.hpp"

namespace Templi
{
	auto delete_file(const std::string& path) -> void;
	auto delete_folder(const std::string& path) -> void;
	auto save_file(const std::string& path, const std::string& text) -> void;
	auto save_file(const std::string& path, const nlohmann::json& text) -> void;
	auto rename(const std::string& old_path, const std::string& new_path) -> void;
	auto copy_folder(const std::string& source, const std::string& destination) -> void;

	auto get_files_with_placeholder(const std::string& path,
		const std::vector<std::string>& exclude_path = {}) -> std::vector<std::string>;

	auto process_each_files(const std::string& path,
		const std::vector<std::string>& exclude_path = {}) -> std::vector<std::string>;

	auto process_for_each_line(const std::string& path,
		std::function<void(const std::string& line_content)> process) -> void;
}  // namespace Templi
