#include <iostream>
#include <Templi/Templi.hpp>
#include <Templi/string.hpp>
#include <Templi/file.hpp>
#include <sstream>

using namespace Templi;

SetString Templi::configure(VectorString paths, String configPath){
    SetString wordsConfig;
    VectorConfig results;
    
    for(const auto path: paths){
        size_t line{1};
        std::ifstream fileTemplate(path);
        std::stringstream contentCleaned;
        String lineContent;

        if(!fileTemplate.is_open())
            continue;

        while(std::getline(fileTemplate, lineContent)){
            VectorPairSI words = parseTemplateString(lineContent);
            contentCleaned << lineContent << "\n";
            if(words.size() > 0){
                results.push_back({path,line,words});
            }
            line++;
        }
        
        fileTemplate.close();
        std::ofstream fileTemplateWrite(path);
        
        if(fileTemplateWrite.is_open()){
            fileTemplateWrite << contentCleaned.str();
            fileTemplateWrite.close();
        }
    }
    
    String configContent = "";
    for(const auto configLine : results){
        configContent +=  std::get<0>(configLine) + " " 
            + std::to_string(std::get<1>(configLine));

        for(const auto word : std::get<2>(configLine)){
            configContent += " " + word.first + " " + std::to_string(word.second);
            wordsConfig.insert(word.first);
        }
        configContent += "\n";
    }
    
    Templi::saveFile(configPath, configContent);
    return wordsConfig;
}

void Templi::generate(String configPath, std::map<String, String> values, std::map<String, String> outputs){
    VectorConfig configs = parseConfigFile(configPath);
    std::ifstream templateFile;
    std::stringstream fileContent;
    String lastFile = "";
    size_t line{1};
    
    for(size_t i =0; i < configs.size(); i++){
        const auto config = configs.at(i);
        String lineContent;
        String fileName = std::get<0>(config);
        size_t fileLine = std::get<1>(config);
        bool findConfig = false;

        if(outputs.find(fileName) == outputs.end())
            continue;
        
        if(fileName != lastFile){
            if(templateFile.is_open()){
                while(std::getline(templateFile, lineContent)){
                    fileContent << lineContent << "\n";
                }
                String fileContentString = fileContent.str();
                saveFile(outputs.at(lastFile), fileContentString);
                templateFile.close();
            }
            
            templateFile.open(fileName);
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
            String fileContentString = fileContent.str();
            saveFile(outputs.at(fileName),fileContentString);
        }
    }
    templateFile.close();
}