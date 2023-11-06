#include <Templi/Cli/Templi_Cli.hpp>
#include <Templi/TempliConfig.hpp>
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

void Templi::cleanInput(std::string &text){
    TColor::set_color(TColor::YELLOW);
    std::getline(std::cin, text);
    text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
    TColor::set_color(TColor::BLUE);
}