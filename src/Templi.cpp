#include <iostream>
#include <Templi/Templi.hpp>
#include <Templi/string.hpp>
#include <Templi/file.hpp>
#include <sstream>
#include <tuple>
#include <vector>

void saveContent(std::string path, std::string content){
    Templi::deleteFile(path);
    Templi::saveOrUpdate(path, content);
}

bool Templi::configureFile(std::string path,std::string outputPath, std::string configPath){
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
            + outputPath + "/" 
            + std::get<0>(configLine) + "/" 
            + std::to_string(std::get<1>(configLine)) + "/"
            + std::to_string(std::get<2>(configLine)) + "\n";
    }

    return Templi::saveOrUpdate(configPath, configContent);
}


bool Templi::writeFile(std::string configPath, std::map<std::string, std::string> values){
    std::vector<std::tuple<std::string, std::string,std::string, int, int >> configs = Templi::extractConfigValue(configPath, values);
    std::stringstream fileContent;
    std::string lastFile = "";
    std::ifstream templateFile;
    int line{1};

    for(const auto config: configs){
        const std::string fileName = std::get<0>(config), outputFile = std::get<1>(config);
        const int index = std::get<4>(config);
        std::string lineContent;

        if(outputFile != lastFile){
            if(lastFile != ""){
                saveContent(lastFile, fileContent.str());
            }
            fileContent.str("");
            lastFile = outputFile;
            templateFile.close();
            templateFile.open(fileName);
        }

        if(templateFile.is_open()){
            while(std::getline(templateFile,lineContent)){
               if(line == std::get<3>(config)){
                    if(index <= lineContent.size()){
                        lineContent.insert(std::get<4>(config), std::get<2>(config));
                    }
                    fileContent << lineContent << "\n";
                    break;
                }else{
                    fileContent << lineContent << "\n";
                }
            }
        }
    }
    
    saveContent(lastFile, fileContent.str());
    return true;
}