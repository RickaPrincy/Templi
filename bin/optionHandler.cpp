#include <Templi/Cli/Templi_Cli.hpp>
#include <iostream>

using namespace Templi;

void Templi::optionHandler(const char *optionChar){
    const std::string option = optionChar;
   
    if(option == "--version" || option == "-v")
        Templi::writeVersion();
    else if(option == "--configure" || option == "-c")
        Templi::takeConfiguration();
    else if(option == "--generate" || option == "-g")
        Templi::generate();
    else
        Templi::writeHelp();
}