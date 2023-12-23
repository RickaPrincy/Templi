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
    if(!config_content.is_object()){
        throw InvalidConfigTypeError("keys", "object");
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

    return config_json;
}

MapString Templi::get_values_from_config(String template_path){
    json config_json = read_templi_config(template_path);
    valid_templi_config(config_json);

    json keys = config_json["keys"];
    MapString result;
    
    for (auto it = keys.begin(); it != keys.end(); ++it) {
        if(it.value().is_string()){
            result.insert(std::make_pair(it.key(), it.value()));
        }else{
            TColor::write_endl(TColor::RED, "[ ERROR ]: keys must be string value");
            exit(EXIT_FAILURE);
        }
    }
    return result;
}