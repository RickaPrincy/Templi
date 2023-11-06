#include <Templi/string.hpp>

std::vector<std::pair<std::string, int>> Templi::getWordWithIndex(std::string text){
    std::vector<std::pair<std::string, int>> results;
    
    size_t pos = text.find("{{");

    while (pos != std::string::npos) {
        size_t startPos = pos + 2;
        size_t endPos = text.find("}}", startPos); 

        if (endPos != std::string::npos) {
            size_t wordLength = endPos - startPos;
            std::string word = text.substr(startPos, wordLength);
            results.push_back(std::make_pair(word, static_cast<int>(pos)));
            pos = text.find("{{", endPos);
        } else {
            break;
        }
    }
        
    return results;
}