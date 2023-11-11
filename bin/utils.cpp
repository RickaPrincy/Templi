#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/file.hpp>
#include <TColor/TColor.hpp>
#include <algorithm>

std::string Templi::repeat(std::string text, int number){
    return number < 1 ? text : text + Templi::repeat(text, --number);
}

void Templi::writeLine(int number){
    TColor::write_endl(TColor::BLUE,"\n" + Templi::repeat("*", number));
}

void Templi::writeKeyValue(std::string key, std::string value){
    TColor::write(TColor::BLUE,"\t" + key);
    TColor::write_endl(TColor::YELLOW, ": " + value);
}

void Templi::writeKeyValue(std::initializer_list<std::pair<std::string, std::string>> keyValue){
    for(const auto pair : keyValue){
        Templi::writeKeyValue(pair.first, pair.second);
    }
}

std::string Templi::getVersion(){
    return "v" + std::to_string(Templi_VERSION_MAJOR) + 
        "." +  std::to_string(Templi_VERSION_MINOR) + 
        "." + std::to_string(Templi_VERSION_PATCH);
}

void Templi::writeTitle(std::string title){
    Templi::writeLine();
    const int row = ( 70 - title.length() ) / 2 - 1;
    std::cout << Templi::repeat("*", row);
    TColor::write(TColor::YELLOW, " " + title + " " );
    TColor::write_endl(TColor::BLUE, Templi::repeat("*", row));
}

void Templi::writeHelp(){
    Templi::writeTitle("Templi@" + Templi::getVersion()  + " options list");
}

void Templi::writeVersion(){
    Templi::writeLine();
    Templi::writeKeyValue({
        {"Name", "Templi"},
        {"Version", Templi::getVersion()},
        {"Github", "https://github.com/RickaPrincy/Templi.git"},
        {"Author", "RickaPrincy <https://github.com/RickaPrincy>"}
    });
    Templi::writeLine();
}

void Templi::getInput(std::string text, std::string &value, bool cleanOutput, std::string defaultValue){
    TColor::write(TColor::BLUE, text + ": ");
    TColor::set_color(TColor::YELLOW);
    std::getline(std::cin, value);
    
    if(cleanOutput)
        value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
    if(!defaultValue.empty() && value.empty())
        value = defaultValue;
    TColor::set_color(TColor::BLUE);
}

std::map<std::string, std::string> Templi::getAllValues(std::vector<std::string> valuesName, std::string text, bool cleanText){
    std::map<std::string, std::string> results;

    for(const auto name: valuesName){
        std::string value = "";
        Templi::getInput(text + " \"" + name + "\"", value, cleanText);
        
        if(!value.empty()){
            results.insert({name, value});
        }
    }

    return results;
}