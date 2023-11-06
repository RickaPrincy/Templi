#include <Templi/string.hpp>
#include <iostream>
#include <regex>

std::vector<std::pair<std::string, int>> Templi::getWordWithIndex(std::string &text){
    std::vector<std::pair<std::string, int>> results;
    
    size_t pos = text.find("{{");

    while (pos != std::string::npos) {
        size_t startPos = pos + 2;
        size_t endPos = text.find("}}", startPos); 

        if (endPos != std::string::npos) {
            size_t wordLength = endPos - startPos;
            std::string word = text.substr(startPos, wordLength);
            results.push_back(std::make_pair(word, static_cast<int>(pos)));

            text.erase(pos, endPos - pos + 2);
            pos = text.find("{{", pos);
        } else {
            break;
        }
    }
        
    return results;
}

std::tuple<std::string,std::string, int, int> Templi::extractValues(std::string &config){
    std::tuple<std::string,std::string, int, int> result = {"","",-1,-1};
    std::regex pattern("([\\w]+)/([\\w]+)/([0-9]+)/([0-9]+)");
    std::smatch matches;

    if(std::regex_match(config, matches, pattern)){
        std::string file = matches[1].str();
        std::string word = matches[2].str();
        int line = std::stoi(matches[3].str());
        int column = std::stoi(matches[4].str());

        result = std::make_tuple(file, word, line, column);
    }else{
        //TODO : should throw error here
        std::cerr << "Config file syntax error" << std::endl;
    }

    return result;
}