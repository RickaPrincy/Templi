#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/file.hpp>
#include <Templi/Templi.hpp>
#include <TColor/TColor.hpp>

void Templi::generate(){
    Templi::writeLine();
    std::string configFileName;
    std::vector<std::string> words, files;
    std::map<std::string, std::string> valuesMap, filesMap;

    Templi::getInput("Config file (default: 'config.templi'): ", configFileName, true, "config.templi");
    words = Templi::readFileByLine(configFileName + ".words");
    files = Templi::readFileByLine(configFileName + ".files");

    valuesMap = Templi::getAllValues(words, "Enter value for");
    filesMap = Templi::getAllValues(files, "Enter outputs path for", true);

    TColor::write_endl(TColor::YELLOW, "Generating template...");
    Templi::generate(configFileName, valuesMap, filesMap);
    TColor::write_endl(TColor::GREEN, "Generating template success !");
}
