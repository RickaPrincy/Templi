#include <Templi/Templi.hpp>
#include <Templi/fs_utils.hpp>
#include <Templi/parser.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/config.hpp>
#include <iostream>
#include <TColor/TColor.hpp>

using namespace Templi;

void Templi::generate(String template_path, String output_path, MapString values, VectorString ignored_path){
    VectorString files;
    get_folder_files(template_path, files, ignored_path);
    
    if(!files.empty()){
        copy_folder(template_path, output_path);
        delete_file(output_path + TEMPLI_SEPARATOR + "templi.json");
    }

    for(auto file: files){
        auto path = output_path + file.substr(template_path.size());
        file_brackets_parser(file, path, values);
    }

    TColor::write_endl(TColor::YELLOW, "[ DONE ]: Your project was generated successfully");
}

void Templi::configure(String template_path, VectorString ignored_path){
    VectorString files;
    SetString words;

    get_folder_files(template_path, files, ignored_path);
    json config_content = {
        {"ignored_paths", ignored_path},
        {"keys", json::array()}
    };
    config_content["ignored_paths"].push_back("templi.json");
    
    for(auto file: files){
        SetString words_found = file_get_brackets_words(file);
        
        if(words_found.empty()){
            config_content["ignored_paths"].push_back(file.substr(template_path.size() + 1));
        }        
        
        for(auto word_found: words_found){
            words.insert(word_found);
        }
    }

    for(auto word: words) {
        json new_word = {
            {"key", word},
            {"type", "input"},
            {"label", ""}
        };
        config_content["keys"].push_back(new_word);
    }
    save_file(template_path + TEMPLI_SEPARATOR + "templi.json", config_content);
}