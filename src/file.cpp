#include <Templi/file.hpp>
#include <Templi/string.hpp>
#include <cstdio>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool Templi::saveFile(std::string path, std::string &text){
    std::ofstream file(path);
    return writeOpenedFile(&file, text);
}

bool Templi::deleteFile(std::string path){
    return std::remove(path.c_str()) != 0;
}

bool Templi::writeOpenedFile(std::ofstream *file,std::string &text){
    if (file->is_open()) {
        *file << text;
        file->close();
        return true;
    }
    return false;
}

std::vector<std::string> Templi::readFileByLine(std::string path){
    std::vector<std::string> result;
    std::ifstream file(path);
    std::string lineContent;
    
    if(file.is_open()){
        while(std::getline(file, lineContent)){
            result.push_back(lineContent);
        }
    }

    return result;
}

void Templi::getFolderFiles(std::string path,std::vector<std::string> &result, std::vector<std::string> excludePaths){
    if(fs::exists(path) && fs::is_directory(path)){
        for(const auto &file: fs::directory_iterator(path)){
            result.push_back(file.path().filename());
        }
    }
    
    return result;
}

std::vector<Templi::TempliConfig> Templi::parseConfigFile(std::string configPath){
    std::vector<Templi::TempliConfig> extracted;
    std::ifstream configFile(configPath);
    std::string lineContent;

    if(!configFile.is_open())
        extracted;
    
    while(std::getline(configFile, lineContent)){
        Templi::TempliConfig value = Templi::parseConfigString(lineContent);
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