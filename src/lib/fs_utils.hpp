#pragma once

#include <Templi/types.hpp>
#include <fstream>
#include <functional>

#include "json.hpp"

namespace Templi
{
	void write_in_open_file(std::ofstream *file, std::string &text);

	void save_file(std::string path, std::string text);
	void save_file(std::string path, nlohmann::json text);
	void delete_file(std::string path);
    void delete_folder(std::string path);

	void copy_folder(std::string source, std::string destination);
	void get_folder_files(std::string path, std::vector<std::string> &result, std::vector<std::string> exclude_path = {});

	void process_for_each_line(std::string path,
		std::function<void(const std::string &line_content)> process);
}  // namespace Templi
