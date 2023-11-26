#include <TColor/TColor.hpp>
#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/file.hpp>
#include <Templi/Templi.hpp>

#include <iostream>
#include <algorithm>
#include <filesystem>

using namespace Templi;

void Templi::takeConfiguration(){
    bool runConfigure = true;
    VectorString filePaths;
    std::vector<std::pair<String, String>> files;
    String configFileName, templateFolder;

    writeLine();
    getInput("Config file (default: 'config.templi')",configFileName,true,"config.templi");
    getInput("Template folder(default: 'template')",templateFolder,true,"template");

    getFolderFiles(templateFolder, filePaths);
    
    launchConfiguration(configFileName,templateFolder,filePaths);
}

void Templi::launchConfiguration(String config,String folderTemplate,VectorString &files){
    SetString wordsConfig;
    String folderPath = "";
    try{
        folderPath = std::filesystem::canonical("./" + folderTemplate);
    }catch(const std::filesystem::filesystem_error &error){
        TColor::write_endl(TColor::RED, "[ ERROR ] : Template folder not found");
        return;
    }

    for(size_t i = 0; i < files.size() ; i++){
        TColor::write_endl(TColor::YELLOW, "This file will be configured " + files.at(i) + "...");
    }

    TColor::write_endl(TColor::YELLOW, "Configuration launched...");
    wordsConfig = configure(files, config);
    
    TColor::write_endl(TColor::YELLOW, "Memorization of the found files...");
    saveIterator(config +".files", files, "\n");
    
    TColor::write_endl(TColor::YELLOW, "Memorization of the found words...");
    saveIterator(config +".words", wordsConfig, "\n");
    
    TColor::write(TColor::GREEN, "Configuration finished!, run ");
    TColor::write(TColor::YELLOW, "templi --generate ");
    TColor::write_endl(TColor::GREEN, "to create template");
}