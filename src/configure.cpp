#include <iostream>
#include <Templi/Templi.hpp>
#include <Templi/string.hpp>
#include <Templi/file.hpp>
#include <sstream>

using namespace Templi;

void Templi::configure(String templateFolder,String configuredPath, VectorString ignoredPaths){
    VectorString paths; // paths of files to configure in the templateFolder
    VectorConfig results;
    SetString wordsConfig; // words founded in all paths
    String prefix; // absolute path to the configured template

    if(!copyFolder(templateFolder, configuredPath))
        return;
    
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
        std::ofstream fileTemplateWrite(configuredPath + path.substr(templateFolder.size()));
        
        if(fileTemplateWrite.is_open()){
            fileTemplateWrite << contentCleaned.str();
            fileTemplateWrite.close();
        }
    }
    Templi::writeConfigContent(templateFolder, configuredPath, results);
}