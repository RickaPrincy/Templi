#include <Templi/string.hpp>
#include <iostream>
#include <regex>

std::vector<std::pair<std::string, int>> Templi::parseTemplateString(std::string &text){
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

Templi::TempliConfig Templi::parseConfigString(std::string &config) {
    std::string fileName = "";
    int fileLine = -1;
    std::vector<std::pair<std::string, int>> pairs = {};
    std::regex configPattern(R"((\S+)\s+(\d+)\s+((\S+\s+\d+\s*)+))");

    std::smatch match;
    if (std::regex_search(config, match, configPattern)) {
        fileName = match[1];
        fileLine = std::stoi(match[2]);

        std::regex pairPattern(R"((\S+)\s+(\d+))");
        std::sregex_iterator pairIterator(match[3].first, match[3].second, pairPattern);
        std::sregex_iterator end;

        for (; pairIterator != end; ++pairIterator) {
            std::string value = (*pairIterator)[1];
            int column = std::stoi((*pairIterator)[2]);
            pairs.push_back({value, column});
        }
    }

    return std::make_tuple(fileName, fileLine, pairs);
}