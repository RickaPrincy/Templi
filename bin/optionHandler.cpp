#include <Templi/Cli/Templi_Cli.hpp>
#include <iostream>

using namespace Templi;

void Templi::optionHandler(const char *optionChar){
    const String option = optionChar;
   
    if(option == "--version" || option == "-v")
        writeVersion();
    else if(option == "--configure" || option == "-c")
        takeConfiguration();
    else if(option == "--generate" || option == "-g")
        generate();
    else
        writeHelp();
}