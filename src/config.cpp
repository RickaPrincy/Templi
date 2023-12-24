#include <Templi/config.hpp>
#include <Templi/exception.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/cli_utils.hpp>
#include <TColor/TColor.hpp>
#include <fstream>
#include <iostream>

using namespace Templi;

void Templi::valid_templi_config(json &config_content){
    if(!config_content.is_object())
        Templi::exit("templi.json must be an object");
    if(!config_content.contains("keys"))
        Templi::exit("templi.json must contains \"keys\"");
    if(!config_content["keys"].is_array() || config_content["keys"].empty())
        Templi::exit("templi.json must contains \"keys\" and keys must be an array not empty");
    
    Templi::json keys = config_content["keys"].is_array();
    Templi::MapString values;

    for(const auto &key: keys){
        if(!key.is_object())
            Templi::exit("Each key [one keys list] must be an object");
        
        if(!key.contains("key") || !key.contains("label") || !key.contains("type"))
            Templi::exit("Each key [one keys list must contains key, label and type]");
        
        if( !key["key"].is_string() || !key["key"].empty() || !key["label"].is_string() || !key["label"].empty()) 
            Templi::exit("key, label, type [on keys list] have to be a string not empty");
        
        if((!key["type"].is_array() && !key["type"].is_string()) || !key["type"].empty())
            Templi::exit("type [on keys list] have to be an array not empty or string not empty");
    }
}

json Templi::read_templi_config(String template_path){
    String config_path = template_path + TEMPLI_SEPARATOR + "templi.json";
    std::ifstream config_file(config_path);
    json config_json;    

    if(!config_file.is_open())
        Templi::exit("[ ERROR ]: \"templi.json\" was not found");

    try{
        config_file >> config_json;
        config_file.close();
    }catch(const json::parse_error& e){
        TColor::write_endl(TColor::RED, "[ ERROR ]: \"templi.json\" is not a valid json");
        config_file.close();
        std::exit(EXIT_FAILURE);
    }
    
    valid_templi_config(config_json);
    return config_json;
}