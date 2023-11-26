#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/file.hpp>
#include <TColor/TColor.hpp>
#include <algorithm>

using namespace Templi;

String Templi::repeat(String text, int number){
    return number < 1 ? text : text + Templi::repeat(text, --number);
}

void Templi::writeLine(int number){
    TColor::write_endl(TColor::BLUE,Templi::repeat("*", number));
}

void Templi::writeKeyValue(String key, String value){
    TColor::write(TColor::BLUE,"\t" + key);
    TColor::write_endl(TColor::YELLOW, ": " + value);
}

void Templi::writeKeyValue(std::initializer_list<std::pair<String, String>> keyValue){
    for(const auto pair : keyValue){
        writeKeyValue(pair.first, pair.second);
    }
}

String Templi::getVersion(){
    return "v" + std::to_string(Templi_VERSION_MAJOR) + 
        "." +  std::to_string(Templi_VERSION_MINOR) + 
        "." + std::to_string(Templi_VERSION_PATCH);
}

void Templi::writeTitle(String title){
    Templi::writeLine();
    const int row = ( 70 - title.length() ) / 2 - 1;
    std::cout << Templi::repeat("*", row);
    TColor::write(TColor::YELLOW, " " + title + " " );
    TColor::write_endl(TColor::BLUE, Templi::repeat("*", row));
}

void Templi::writeHelp(){
    writeTitle("Templi@" + Templi::getVersion()  + " options list");
}

void Templi::writeVersion(){
    writeLine();
    writeKeyValue({
        {"Name", "Templi"},
        {"Version", Templi::getVersion()},
        {"Github", "https://github.com/RickaPrincy/Templi.git"},
        {"Author", "RickaPrincy <https://github.com/RickaPrincy>"}
    });
    writeLine();
}

void Templi::getInput(String text, String &value, bool cleanOutput, String defaultValue){
    TColor::write(TColor::BLUE, text + ": ");
    TColor::set_color(TColor::YELLOW);
    std::getline(std::cin, value);
    
    if(cleanOutput)
        value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
    if(!defaultValue.empty() && value.empty())
        value = defaultValue;
    TColor::set_color(TColor::BLUE);
}

MapString Templi::getAllValues(VectorString valuesName, String text, bool cleanText){
    MapString results;
    
    for(const auto name: valuesName){
        String value = "";
        getInput(text + " \"" + name + "\"", value, cleanText);
        
        if(!value.empty()){
            results.insert({name, value});
        }
    }

    return results;
}