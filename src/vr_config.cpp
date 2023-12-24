#include <Templi/vr_config.hpp>
#include <Templi/exception.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/cli_utils.hpp>
#include <TColor/TColor.hpp>
#include <fstream>
#include <iostream>

using namespace Templi;

json Templi::vr_templi_file(String config_path){
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
    return config_json;
}

void Templi::v_templi_structure(json &config_content){
    if (!config_content.is_object())
        Templi::exit("templi.json must be an object");
    if (!config_content.contains("keys"))
        Templi::exit("templi.json must contain \"keys\"");
    if (!config_content["keys"].is_array() || config_content["keys"].empty())
        Templi::exit("templi.json must contain \"keys\" and keys must be a non-empty array");
}

MapString Templi::vr_templi_keys(json &config_content){
    json keys = config_content["keys"];
    MapString values; 

    for (const auto &key : keys) {
        RCli::InputConfig config;
        VectorString options;

        if (!key.is_object())
            Templi::exit("Each key [in keys list] must be an object");

        if (!key.contains("key") || !key.contains("label") || !key.contains("type"))
            Templi::exit("Each key [in keys list] must contain key, label, and type");

        if (!key["key"].is_string() || key["key"].empty() || !key["label"].is_string() || key["label"].empty())
            Templi::exit("key and label [in keys list] have to be a non-empty string");
        
        if ((!key["type"].is_array() && !key["type"].is_string()) || key["type"].empty())
            Templi::exit("type [in keys list] must be an array or string and not empty");

        if (key["type"].is_array()) {
            for (auto type : key["type"])
                if (!type.is_string())
                    Templi::exit("type items [in keys list] must be a string");
            options = key["type"];
        }

        if (key["type"].is_string()) {
            if (key["type"] != "input" && key["type"] != "bool")
                Templi::exit("type [if string] [in keys list] must be \"input\" or \"bool\"");
        }
        
        config.text(key["label"]);
        
        //------------------optional attribute-----------------

        if(key.contains("required")){
            if(key["required"].is_boolean())
                config.required(key["required"]);
            else
                Templi::exit("required [in key list] must be a boolean");
        }

        if(key.contains("clean")){
            if(key["clean"].is_boolean())
                config.clean(key["clean"]);
            else
                Templi::exit("clean [in key list] must be a boolean");
        }
        
        if(key.contains("default")){
            if(!options.empty() || key["type"] != "bool"){
                if(key["default"].is_string())
                    config.default_value(key["default"]);
                else
                    Templi::exit("default [if type != bool] [in key list] must be a string");
            }else if(!key["default"].is_boolean()){
                Templi::exit("default [if type == bool] [in key list] must be a boolean");
            }
        }
        
        if(!options.empty())
            values.insert(std::make_pair(key["key"], RCli::ask_value_in_options(config._text, options)));
        else if(key["type"] == "bool"){
            bool default_value = true;
            if(key.contains("default")) 
                default_value = key["default"];
            values.insert(std::make_pair(key["key"], std::to_string(RCli::ask_boolean(config._text, default_value))));
        }
        else
            values.insert(std::make_pair(key["key"], RCli::ask_input_value(config)));
    }
    
    return values;
}

Templi::MapString Templi::read_templi_config(String template_path){
    String config_path = template_path + TEMPLI_SEPARATOR + "templi.json";
    Templi::json file_content = Templi::vr_templi_file(config_path);
    v_templi_structure(file_content);
    return vr_templi_keys(file_content);
}