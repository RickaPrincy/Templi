#include <iostream>
#include <Templi/Templi.hpp>
#include <Templi/string.hpp>
#include <Templi/file.hpp>
#include <sstream>

using namespace Templi;

void Templi::generate(String configuredPath,String outputFolder, MapString values){
    VectorConfig configs = Templi::parseConfigFile(configuredPath + "/config.templi");
    std::ifstream templateFile;
    std::stringstream fileContent;
    String lastFile = "";
    size_t line{1};

    if(!copyFolder(configuredPath, outputFolder))
        return;

    Templi::deleteFile(outputFolder + "/config.templi");
    Templi::deleteFile(outputFolder + "/config.templi.words");

    for(size_t i = 0; i < configs.size(); i++){
        const auto config = configs.at(i);
        String lineContent;
        String fileName = std::get<0>(config);
        size_t fileLine = std::get<1>(config);
        bool findConfig = false;

        if(fileName != lastFile){
            if(templateFile.is_open()){
                while(std::getline(templateFile, lineContent)){
                    fileContent << lineContent << "\n";
                }
                String fileContentString = fileContent.str();
                Templi::saveFile(outputFolder + lastFile, fileContentString);
                templateFile.close();
            }
            
            templateFile.open(outputFolder  + fileName);
            lastFile = fileName;
            fileContent.str("");
            line = 1;
            if(!templateFile.is_open()){
                //TODO: ERROR
                continue;
            }
        }
        
        while(std::getline(templateFile, lineContent)){
            if(line == fileLine){
                size_t additionalIndex = 0;
                for(const auto pair: std::get<2>(config)){
                    if(values.find(pair.first) != values.end()){
                        const auto value = values.at(pair.first);
                        if(pair.second <= lineContent.size()){
                            lineContent.insert(pair.second + additionalIndex, value);
                            additionalIndex += value.size();
                        }
                    }else{
                        //TODO: when one value is missing
                    }
                }
                findConfig = true;
            }
            fileContent << lineContent << "\n";
            line++;

            if(findConfig)
                break;
        }

        if(!findConfig || i == configs.size() - 1){
            while(std::getline(templateFile, lineContent)){
                fileContent << lineContent << "\n";
            }
            String fileContentString = fileContent.str();
            Templi::saveFile(outputFolder + fileName,fileContentString);
        }
    }

    templateFile.close();
}