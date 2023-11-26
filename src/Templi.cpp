#include <iostream>
#include <Templi/Templi.hpp>
#include <Templi/string.hpp>
#include <Templi/file.hpp>
#include <sstream>

using namespace Templi;

SetString Templi::configure(String templateFolder,String configuredPath, VectorString ignoredPaths){
    VectorString paths; // paths of files to configure in the templateFolder
    VectorConfig results;
    SetString wordsConfig; // words founded in all paths
    String prefix; // absolute path to the configured template

    if(!copyFolder(templateFolder, configuredPath))
        return wordsConfig;
    
    prefix = absolutePath(configuredPath);
    getFolderFiles(templateFolder,paths, ignoredPaths);

    for(const auto path: paths){
        size_t line{1};
        std::ifstream fileTemplate(path);
        std::stringstream contentCleaned;
        String lineContent;

        if(!fileTemplate.is_open())
            continue;
        
        while(std::getline(fileTemplate, lineContent)){
            VectorPairSI words = Templi::parseTemplateString(lineContent);
            contentCleaned << lineContent << "\n";
            if(words.size() > 0){
                results.push_back({path,line,words});
            }
            line++;
        }

        fileTemplate.close();
        std::ofstream fileTemplateWrite(prefix + path.substr(templateFolder.size()));
        
        if(fileTemplateWrite.is_open()){
            fileTemplateWrite << contentCleaned.str();
            fileTemplateWrite.close();
        }
    }

    std::string configContent = "";
    for(const auto configLine : results){
        configContent +=  std::get<0>(configLine).substr(templateFolder.size()) + " " 
            + std::to_string(std::get<1>(configLine));

        for(const auto word : std::get<2>(configLine)){
            configContent += " " + word.first + " " + std::to_string(word.second);
            wordsConfig.insert(word.first);
        }
        configContent += "\n";
    }
    
    Templi::saveFile(prefix + "/config.templi", configContent);
    Templi::saveFile(prefix + "/config.templi.prefix", prefix);

    return wordsConfig;
}

void Templi::generate(String configuredPath,String outputFolder, MapString values){
    return;
}