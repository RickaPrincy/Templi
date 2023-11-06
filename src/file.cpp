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

std::vector<std::map<std::string,std::pair<int, int>>> Templi::findPosition(std::string filePath, std::string word){
    std::vector<std::map<std::string,std::pair<int, int>>> index;
    std::ifstream file(filePath);

    if(file.is_open()){
        int line{0};
        std::string lineValue;
        
        while(std::getline(file, lineValue)){

        }
        file.close();
    }
    
    return index;
}