#include "fs_utils.hpp"

#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iterator>

namespace fs = std::filesystem;
using namespace Templi;

static void write_in_open_file(std::ofstream *file, std::string &text)
{
	if (file->is_open())
	{
		*file << text;
		file->close();
		return;
	}
	throw Templi::Exception("Cannot save text to a file which is not open");
}

void Templi::save_file(std::string path, nlohmann::json text)
{
	std::ofstream file(path);
	if (file.is_open())
	{
		file << text.dump(2);
		return;
	}
	throw Templi::Exception("Cannot save " + path);
}

void Templi::rename(const std::string &old_path, const std::string &new_path)
{
	if (!fs::exists(old_path))
	{
		throw Templi::Exception("Path does not exist: " + old_path);
	}

	try
	{
		fs::rename(old_path, new_path);
	}
	catch (const std::filesystem::filesystem_error &e)
	{
		throw Templi::Exception("Cannot rename " + old_path + " to " + new_path + ": " + e.what());
	}
}

void Templi::save_file(std::string path, std::string text)
{
	std::ofstream file(path);
	write_in_open_file(&file, text);
}

void Templi::delete_file(std::string path)
{
	if (std::remove(path.c_str()) != 0)
		throw Templi::Exception("Cannot delete " + path);
}

void Templi::copy_folder(std::string source, std::string destination)
{
	try
	{
		fs::copy(source,
			destination,
			fs::copy_options::recursive | fs::copy_options::overwrite_existing);
	}
	catch (const std::exception &e)
	{
		throw Templi::Exception("Error when try to copy " + source + " to " + destination);
	}
}

void Templi::process_for_each_line(std::string path,
	std::function<void(const std::string &line_content)> process)
{
	std::ifstream file(path);

	if (!file.is_open())
		throw Templi::Exception("Cannot open " + path);

	std::string line;

	while (std::getline(file, line))
		process(line);

	file.close();
}

void Templi::delete_folder(std::string path)
{
	if (!fs::exists(path))
	{
		return;
	}

	try
	{
		fs::remove_all(path);
	}
	catch (const std::filesystem::filesystem_error &e)
	{
		std::string message = e.what();
		throw Templi::Exception(message);
	}
}

static void get_folder_files_process(const std::string &path,
	std::vector<std::string> &result,
	const std::vector<std::string> &exclude_paths)
{
	auto it = std::find(exclude_paths.begin(), exclude_paths.end(), path);
	if (it != exclude_paths.end())
	{
		return;
	}

	if (!fs::exists(path) || !fs::is_directory(path))
	{
		throw std::runtime_error(path + " is not a folder");
	}

	for (const auto &file : fs::directory_iterator(path))
	{
		std::string file_path = file.path().string();
		auto it = std::find(exclude_paths.begin(), exclude_paths.end(), file_path);
		if (it != exclude_paths.end())
		{
			continue;
		}

		if (fs::is_directory(file_path))
		{
			get_folder_files_process(file_path, result, exclude_paths);
		}
		else if (fs::is_regular_file(file_path))
		{
			result.push_back(file_path);
		}
	}
}

std::vector<std::string> Templi::get_files_with_placeholder(std::string template_path,
	std::vector<std::string> exclude_paths)
{
	std::vector<std::string> results{};
	std::vector<std::string> relative_exclude_paths{};

	std::transform(exclude_paths.begin(),
		exclude_paths.end(),
		std::back_inserter(relative_exclude_paths),
		[&](const std::string path)
		{ return (std::filesystem::path(template_path) / std::filesystem::path(path)).string(); });

	get_folder_files_process(template_path, results, relative_exclude_paths);
	return results;
}
