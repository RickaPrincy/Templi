#include <Templi/Cli/Templi_Cli.hpp>
#include <iostream>

using namespace Templi;

void Templi::optionHandler(const char *optionChar){
    const std::string option = optionChar;
   
    if(option == "--version" || option == "-v")
        Templi::writeVersion();
    else if(option == "--configure" || option == "-c")
        Templi::writeVersion();
    else
        Templi::writeHelp();
}