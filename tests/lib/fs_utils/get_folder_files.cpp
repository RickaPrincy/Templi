#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../../utils.hpp"
#include "fs_utils.hpp"

using namespace Templi;

TEST(FsUtils_get_folder_files, basic_test)
{
	std::string test_path = FIXTURE("fs_utils", "get_folder_files_fixture");

	std::vector<std::string> exclude_paths = {
		"folder1/folder1_ignored_file.txt", "ignored_folder", "ignored_file.txt"
	};

	std::vector<std::string> files = Templi::get_folder_files(test_path, exclude_paths);

	std::vector<std::string> expected_files = {
		"fixtures/fs_utils/get_folder_files_fixture/file1.txt",
		"fixtures/fs_utils/get_folder_files_fixture/file2.txt",
		"fixtures/fs_utils/get_folder_files_fixture/folder1/folder1_file1.txt",
		"fixtures/fs_utils/get_folder_files_fixture/folder1/folder1_file2.txt",
		"fixtures/fs_utils/get_folder_files_fixture/folder2/folder2_folder1/"
		"folder2_folder1_file1.txt",
	};

	std::sort(files.begin(), files.end());
	ASSERT_EQ(files.size(), expected_files.size());
	for (size_t i = 0; i < files.size(); ++i)
	{
		ASSERT_EQ(files[i], expected_files[i]);
	}
}
