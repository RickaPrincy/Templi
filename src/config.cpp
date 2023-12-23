#include <Templi/config.hpp>
#include <Templi/exception.hpp>
#include <Templi/TempliConfig.hpp>
#include <TColor/TColor.hpp>
#include <fstream>
#include <iostream>

using namespace Templi;

void Templi::valid_templi_config(json &config_content){
    if(!config_content.is_object()){
        throw InvalidConfigTypeError("templi.json", "object");
    }
    if(!config_content.contains("keys")){
        throw InvalidConfigNotFound("keys");
    }
    if(!config_content.is_array()){
        throw InvalidConfigTypeError("keys", "array");
    }
}

json Templi::read_templi_config(String template_path){
    String config_path = template_path + TEMPLI_SEPARATOR + "templi.json";
    std::ifstream config_file(config_path);
    json config_json;    

    if(!config_file.is_open()){
        TColor::write_endl(TColor::RED, "[ ERROR ]: \"templi.json\" was not found");
        exit(EXIT_FAILURE);
    }

    try{
        config_file >> config_json;
        config_file.close();
    }catch(const json::parse_error& e){
        TColor::write_endl(TColor::RED, "[ ERROR ]: \"templi.json\" is not a valid json");
        config_file.close();
        exit(EXIT_FAILURE);
    }
    
    valid_templi_config(config_json);
    return config_json;
}