#include <Templi/fs_utils.hpp>
#include <Templi/parser.hpp>
#include <Templi/TempliConfig.hpp>
#include <cstdio>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace Templi;

bool Templi::save_file(String path, json text){
    std::ofstream file(path);
    if (file.is_open()) {
        file << text.dump(2);
        return true;
    }
    return false;
}

bool Templi::save_file(String path, String text){
    std::ofstream file(path);
    return write_in_open_file(&file, text);
}

bool Templi::delete_file(String path){
    return std::remove(path.c_str()) != 0;
}

bool Templi::write_in_open_file(std::ofstream *file,String &text){
    if (file->is_open()) {
        *file << text;
        file->close();
        return true;
    }
    return false;
}

void Templi::get_folder_files(String path,VectorString &result, VectorString exclude_paths){
    if(fs::exists(path) && fs::is_directory(path)){
        for(const auto &file: fs::directory_iterator(path)){
            int i = 0;
            bool notExclude = true;
            
            while( i < exclude_paths.size()){
                if(file.path().string() == path + TEMPLI_SEPARATOR + exclude_paths.at(i)){
                    notExclude = false;
                    break;
                }
                i++;
            }

            if(!notExclude)
                continue;

            if (fs::is_directory(file)) {
                Templi::get_folder_files(file.path().string(), result, exclude_paths);
            } else if (fs::is_regular_file(file)) {
                result.push_back(file.path().string());
            }
        }
    }
}

bool Templi::copy_folder(String source, String destination){
    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Templi::process_for_each_line(String path, std::function<void(const String &line_content)> process){
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        process(line);
    }

    file.close();
    return true;
}