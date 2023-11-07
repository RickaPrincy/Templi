#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/file.hpp>
#include <Templi/Templi.hpp>

void Templi::generate(){
    Templi::writeLine();
    std::string configFileName;
    std::vector<std::string> values;
    std::map<std::string, std::string> valuesMap;

    std::cout << "Config file (default: 'config.templi'): ";
    Templi::cleanInput(configFileName);
    
    if(configFileName.empty())
        configFileName = "config.templi";

    values = Templi::getValuesNames(configFileName + ".words");

    for(const auto &value: values){
        std::string inputResult;
        std::cout << "Enter value for " << value << ": ";
        Templi::cleanInput(inputResult);

        if(!inputResult.empty()){
            valuesMap.insert({value, inputResult});
        }
    }

    Templi::writeFile(configFileName, valuesMap);
}
