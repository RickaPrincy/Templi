#include <TColor/TColor.hpp>
#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/file.hpp>
#include <Templi/Templi.hpp>

#include <iostream>
#include <algorithm>
#include <filesystem>

using namespace Templi;

void Templi::configureCli(){
    String templateFolder, configuredPath, oneIgnoredPath;
    VectorString ignoredPaths; 
    
    Templi::writeLine(); 
    Templi::getInput("Template folder(default: '__template__')", templateFolder, true,"__template__");
    Templi::getInput("Configured path(default: '__configured__')", configuredPath, true,"__configured__");

    while (true) {
        Templi::getInput("Add Path to exclude (Empty if stop adding)", oneIgnoredPath, true);
        if (oneIgnoredPath.empty()) {
            break;
        }
        ignoredPaths.push_back(oneIgnoredPath);
    }

    Templi::configure(templateFolder, configuredPath, ignoredPaths);
    TColor::write(TColor::GREEN, "Configuration finished!, run ");
    TColor::write(TColor::YELLOW, "templi --generate ");
    TColor::write_endl(TColor::GREEN, "to create template");
    Templi::writeLine(); 
}