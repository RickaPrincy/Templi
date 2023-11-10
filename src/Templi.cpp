#include <iostream>
#include <Templi/Templi.hpp>
#include <Templi/string.hpp>
#include <Templi/file.hpp>
#include <sstream>
#include <tuple>
#include <vector>

std::set<std::string> Templi::configure(std::string path,std::string outputPath, std::string configPath){
    std::set<std::string> wordsConfig;
    std::ifstream fileTemplate(path);
    std::stringstream contentCleaned;
    std::string lineContent;
    size_t line{1};
    std::vector<std::tuple<std::string, int, int>> results;

    if(!fileTemplate.is_open())
        wordsConfig;

    while(std::getline(fileTemplate, lineContent)){
        std::vector<std::pair<std::string, int>> words = Templi::parseTemplateString(lineContent);
        contentCleaned << lineContent << "\n";
        for(const auto pair: words){
            results.push_back({pair.first, line, pair.second});
            wordsConfig.insert(pair.first);
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
            path + " " 
            + outputPath + " " 
            + std::get<0>(configLine) + " " 
            + std::to_string(std::get<1>(configLine)) + " "
            + std::to_string(std::get<2>(configLine)) + "\n";
    }

    Templi::saveFile(configPath, configContent);
    return wordsConfig;
}

bool Templi::generate(std::string configPath, std::map<std::string, std::string> values){
    std::vector<std::tuple<std::string, std::string,std::string, int, int >> configs = Templi::parseConfigFile(configPath, values);
    std::stringstream fileContent;
    std::string lastFile = "";
    std::ifstream templateFile;
    int line{0};

    for(const auto config: configs){
        const std::string fileName = std::get<0>(config), outputFile = std::get<1>(config);
        const int index = std::get<4>(config);
        std::string lineContent;

        if(outputFile != lastFile){
            std::string fileContentString = fileContent.str();
            if(lastFile != ""){
                Templi::saveFile(lastFile, fileContentString);
            }
            fileContent.str("");
            lastFile = outputFile;
            templateFile.close();
            templateFile.open(fileName);
        }

        if(templateFile.is_open()){
            while(std::getline(templateFile,lineContent)){
                if(++line == std::get<3>(config)){
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

    std::string fileContentString = fileContent.str();
    Templi::saveFile(lastFile, fileContentString);
    return true;
}