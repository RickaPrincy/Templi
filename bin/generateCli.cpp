#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/file.hpp>
#include <Templi/Templi.hpp>
#include <TColor/TColor.hpp>

using namespace Templi;

void Templi::generateCli(){
    String configuredPath, generatedPath;
    VectorString words;
    MapString valuesMap, filesMap;

    Templi::writeLine();
    Templi::getInput("Configured template: (default: '__configured__'): ", configuredPath, true, "__configured__");
    Templi::getInput("Generated path: (default: '__generated__'): ", generatedPath, true, "__generated__");
    
    words = Templi::readFileByLine(configuredPath + "/config.templi.words");
    valuesMap = Templi::getAllValues(words, "Enter value for");

    TColor::write_endl(TColor::YELLOW, "Generating template...");
    Templi::generate(configuredPath, generatedPath, valuesMap);
    TColor::write_endl(TColor::GREEN, "Generating template success !");
    Templi::writeLine();
}
