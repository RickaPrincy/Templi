#include <Templi/file.hpp>
#include <Templi/string.hpp>
#include <cstdio>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace Templi;

bool Templi::saveFile(String path, String &text){
    std::ofstream file(path);
    return writeOpenedFile(&file, text);
}

bool Templi::deleteFile(String path){
    return std::remove(path.c_str()) != 0;
}

bool Templi::writeOpenedFile(std::ofstream *file,String &text){
    if (file->is_open()) {
        *file << text;
        file->close();
        return true;
    }
    return false;
}

VectorString Templi::readFileByLine(String path){
    VectorString result;
    std::ifstream file(path);
    String lineContent;
    
    if(file.is_open()){
        while(std::getline(file, lineContent)){
            result.push_back(lineContent);
        }
    }

    return result;
}

void Templi::getFolderFiles(String path,VectorString &result, VectorString excludePaths){
    if(fs::exists(path) && fs::is_directory(path)){
        for(const auto &file: fs::directory_iterator(path)){
            int i = 0;
            bool notExclude = true;
            
            while( i < excludePaths.size()){
                if(file.path().string() == excludePaths.at(i)){
                    notExclude = false;
                    break;
                }
                i++;
            }

            if(!notExclude)
                continue;

            if (fs::is_directory(file)) {
                Templi::getFolderFiles(file.path().string(), result, excludePaths);
            } else if (fs::is_regular_file(file)) {
                result.push_back(file.path().string());
            }
        }
    }
}

VectorConfig Templi::parseConfigFile(String configPath){
    VectorConfig extracted;
    std::ifstream configFile(configPath);
    String lineContent;

    if(!configFile.is_open())
        extracted;
    
    while(std::getline(configFile, lineContent)){
        TempliConfig value = parseConfigString(lineContent);
        if(std::get<0>(value) != ""){
            extracted.push_back(value);
        }
        else{
            //TODO: should throw error
            std::cerr << "Config file error" << std::endl;
        }
    }
    configFile.close();
    return extracted;
}

bool Templi::copyFolder(String source, String destination){
    try {
        fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

void Templi::writeConfigContent(String templateFolder, String configuredPath,VectorConfig &configs){
    String configContent = "";
    SetString wordsConfig;
    for(const auto configLine : configs){
        configContent +=  std::get<0>(configLine).substr(templateFolder.size()) + " " 
            + std::to_string(std::get<1>(configLine));
        for(const auto word : std::get<2>(configLine)){
            configContent += " " + word.first + " " + std::to_string(word.second);
            wordsConfig.insert(word.first);
        }
        configContent += "\n";
    }
    
    Templi::saveFile( configuredPath + "/config.templi", configContent);
    Templi::saveIterator(configuredPath + "/config.templi.words", wordsConfig, "\n");
}