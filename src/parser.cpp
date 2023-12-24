#include <Templi/parser.hpp>
#include <iostream>
#include <regex>
#include <Templi/fs_utils.hpp>

using namespace Templi;

String Templi::brackets_parser(String text, MapString values, SetString &words) {
    String result = text;
    size_t pos = result.find("{{");

    while (pos != String::npos) {
        size_t startPos = pos + 2;
        size_t endPos = result.find("}}", startPos);

        if (endPos != String::npos) {
            size_t wordLength = endPos - startPos;
            String word = result.substr(startPos, wordLength);
            
            words.insert(word);
            auto it = values.find(word);
            if (it != values.end()) {
                result.replace(pos, endPos - pos + 2, it->second);
                pos = result.find("{{", pos + it->second.length());
            } else {
                pos = result.find("{{", endPos);
            }
        } else {
            break;
        }
    }

    return result;
}

SetString Templi::get_brackets_words(String text){
    SetString words;
    brackets_parser(text, {}, words);
    return words;
}

String Templi::replace_brackets_words(String text, MapString values){
    SetString words;
    return brackets_parser(text, values, words);
}

SetString Templi::file_get_brackets_words(String file_path){
    SetString words;
    process_for_each_line(file_path, [&](const String &line_content){
        for(auto word: get_brackets_words(line_content)){
            words.insert(word);
        }
    });
    return words;
}

void Templi::file_brackets_parser(String file_path,String output_path, MapString values){
    std::stringstream file_parsed_content;
    
    process_for_each_line(file_path, [&](const String &line_content){
        file_parsed_content << replace_brackets_words(line_content, values) << "\n";
    });
    
    save_file(output_path, file_parsed_content.str());
}