#include <iostream>
#include <Templi/Templi.hpp>
#include <Templi/string.hpp>
#include <Templi/file.hpp>
#include <sstream>
#include <tuple>

bool Templi::configureFile(std::string path, std::string configPath){
    std::ifstream fileTemplate(path);
    std::stringstream contentCleaned;
    std::string lineContent;
    size_t line{1};
    std::vector<std::tuple<std::string, int, int>> results;

    if(!fileTemplate.is_open())
        return false;

    while(std::getline(fileTemplate, lineContent)){
        std::vector<std::pair<std::string, int>> words = Templi::getWordWithIndex(lineContent);
        contentCleaned << lineContent << "\n";
        for(const auto pair: words){
            results.push_back({pair.first, line, pair.second});
        }
        line++;
    }
    fileTemplate.close();

    std::ofstream fileTemplateWrite(path);
    
    if(fileTemplateWrite.is_open()){
        fileTemplateWrite << contentCleaned.str();
        fileTemplateWrite.close();
    }

    std::string configContent = "";
    for(const auto configLine : results){
        configContent += 
            path + "/" 
            + std::get<0>(configLine) + "/" 
            + std::to_string(std::get<1>(configLine)) + "/" 
            + std::to_string(std::get<2>(configLine)) + "\n";
    }

    return Templi::saveOrUpdate(configPath, configContent);
}