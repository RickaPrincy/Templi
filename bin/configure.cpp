#include <TColor/TColor.hpp>
#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/file.hpp>
#include <Templi/Templi.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

void Templi::takeConfiguration(){
    bool runConfigure = true;
    std::vector<std::string> filePaths;
    std::vector<std::pair<std::string, std::string>> files;
    std::string configFileName, templateFolder;

    Templi::writeLine();
    Templi::getInput("Config file (default: 'config.templi')",configFileName,true,"config.templi");
    Templi::getInput("Template folder(default: 'template')",templateFolder,true,"template");

    filePaths = Templi::getFolderFiles(templateFolder);
    
    launchConfiguration(configFileName,templateFolder,filePaths);
}

void Templi::launchConfiguration(std::string config,std::string folderTemplate,std::vector<std::string> &files){
    std::set<std::string> wordsConfig;

    for(size_t i = 0; i < files.size() ; i++){
        TColor::write_endl(TColor::YELLOW, "This file will be configured " + files.at(i) + "...");
        //TODO: change / to \ for windows using cmake
        files.at(i) = folderTemplate + "/" + files.at(i);
    }

    TColor::write_endl(TColor::YELLOW, "Configuration launched...");
    wordsConfig = Templi::configure(files, config);
    
    TColor::write_endl(TColor::YELLOW, "Memorization of the found files...");
    Templi::saveIterator(config +".files", files);
    
    TColor::write_endl(TColor::YELLOW, "Memorization of the found words...");
    Templi::saveIterator(config +".words", wordsConfig);
    
    TColor::write(TColor::GREEN, "Configuration finished!, run ");
    TColor::write(TColor::YELLOW, "templi --generate ");
    TColor::write_endl(TColor::GREEN, "to create template");
}