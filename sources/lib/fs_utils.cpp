#include "fs_utils.hpp"

#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iterator>

namespace fs = std::filesystem;

namespace Templi
{
	static auto write_in_open_file(std::ofstream *file, const std::string &text) -> void
	{
		if (file->is_open())
		{
			*file << text;
			file->close();
			return;
		}
		throw Exception("Cannot save text to a file which is not open");
	}

	auto save_file(const std::string &path, const nlohmann::json &text) -> void
	{
		std::ofstream file(path);
		if (file.is_open())
		{
			file << text.dump(2);
			return;
		}
		throw Exception("Cannot save " + path);
	}

	auto rename(const std::string &old_path, const std::string &new_path) -> void
	{
		if (!fs::exists(old_path))
		{
			throw Exception("Path does not exist: " + old_path);
		}

		try
		{
			fs::rename(old_path, new_path);
		}
		catch (const std::filesystem::filesystem_error &e)
		{
			throw Exception("Cannot rename " + old_path + " to " + new_path + ": " + e.what());
		}
	}

	auto save_file(const std::string &path, const std::string &text) -> void
	{
		std::ofstream file(path);
		write_in_open_file(&file, text);
	}

	auto delete_file(const std::string &path) -> void
	{
		if (std::remove(path.c_str()) != 0)
		{
			throw Exception("Cannot delete " + path);
		}
	}

	auto copy_folder(const std::string &source, const std::string &destination) -> void
	{
		try
		{
			fs::copy(source,
				destination,
				fs::copy_options::recursive | fs::copy_options::overwrite_existing);
		}
		catch (const std::exception &e)
		{
			throw Exception("Error when try to copy " + source + " to " + destination);
		}
	}

	auto process_for_each_line(const std::string &path,
		std::function<void(const std::string &line_content)> process) -> void  // NOLINT
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			throw Exception("Cannot open " + path);
		}

		if (file.good())
		{
			std::string line;
			while (std::getline(file, line))
			{
				process(line);
			}
		}

		file.close();
	}

	auto delete_folder(const std::string &path) -> void
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
			throw Exception(message);
		}
	}

	static auto get_folder_files_process(const std::string &path,
		std::vector<std::string> &result,
		const std::vector<std::string> &exclude_paths) -> void
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

	auto get_files_with_placeholder(const std::string &template_path,
		const std::vector<std::string> &exclude_paths) -> std::vector<std::string>
	{
		std::vector<std::string> results{};
		std::vector<std::string> relative_exclude_paths{};

		std::transform(exclude_paths.begin(),
			exclude_paths.end(),
			std::back_inserter(relative_exclude_paths),
			[&](const std::string &path)
			{
				return (std::filesystem::path(template_path) / std::filesystem::path(path))
					.string();
			});

		get_folder_files_process(template_path, results, relative_exclude_paths);
		return results;
	}
}  // namespace Templi
