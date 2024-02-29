#pragma once

#include <Templi/types.hpp>
#include <fstream>
#include <functional>

#include "json.hpp"

namespace Templi
{
	bool write_in_open_file(std::ofstream *file, String &text);

	bool save_file(String path, String text);
	bool save_file(String path, nlohmann::json text);
	bool delete_file(String path);

	bool copy_folder(String source, String destination);
	void get_folder_files(String path, VectorString &result, VectorString exclude_path = {});

	bool process_for_each_line(String path,
		std::function<void(const String &line_content)> process);
}  // namespace Templi
