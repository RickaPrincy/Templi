#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/file.hpp>
#include <Templi/Templi.hpp>
#include <TColor/TColor.hpp>

using namespace Templi;

void Templi::generate(){
    Templi::writeLine();
    String configFileName;
    VectorString words, files;
    MapString valuesMap, filesMap;

    getInput("Config file (default: 'config.templi'): ", configFileName, true, "config.templi");
    words = readFileByLine(configFileName + ".words");
    files = readFileByLine(configFileName + ".files");

    valuesMap = getAllValues(words, "Enter value for");
    filesMap = getAllValues(files, "Enter outputs path for", true);

    TColor::write_endl(TColor::YELLOW, "Generating template...");
    generate(configFileName, valuesMap, filesMap);
    TColor::write_endl(TColor::GREEN, "Generating template success !");
}
