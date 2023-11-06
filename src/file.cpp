#include <Templi/file.hpp>
#include <fstream>
#include <iostream>
#include <regex>

bool Templi::fileExists(std::string path){
    std::ifstream file(path);
    bool result = file.is_open();
    file.close();

    return result;
}