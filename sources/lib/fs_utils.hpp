#pragma once

#include <Templi/types.hpp>
#include <functional>
#include <vector>

#include "json.hpp"

namespace Templi
{
	void save_file(std::string path, std::string text);
	void save_file(std::string path, nlohmann::json text);
	void delete_file(std::string path);
	void delete_folder(std::string path);
  void rename(const std::string& old_path, const std::string& new_path);

	void copy_folder(std::string source, std::string destination);
	std::vector<std::string> get_folder_files(std::string path,
		std::vector<std::string> exclude_path = {});

	void process_for_each_line(std::string path,
		std::function<void(const std::string &line_content)> process);
}  // namespace Templi
