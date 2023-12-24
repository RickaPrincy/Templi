#include <Templi/config.hpp>
#include <Templi/exception.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/cli_utils.hpp>
#include <TColor/TColor.hpp>
#include <fstream>
#include <iostream>

using namespace Templi;

//Validator
void Templi::validate_templi_config(json &config_content) {
    if (!config_content.is_object())
        Templi::exit("templi.json must be an object");
    if (!config_content.contains("keys"))
        Templi::exit("templi.json must contain \"keys\"");
    if (!config_content["keys"].is_array() || config_content["keys"].empty())
        Templi::exit("templi.json must contain \"keys\" and keys must be a non-empty array");

    Templi::json keys = config_content["keys"];
    Templi::MapString values;

    for (const auto &key : keys) {
        if (!key.is_object())
            Templi::exit("Each key [in keys list] must be an object");

        if (!key.contains("key") || !key.contains("label") || !key.contains("type"))
            Templi::exit("Each key [in keys list] must contain key, label, and type");

        if (!key["key"].is_string() || key["key"].empty() || !key["label"].is_string() || key["label"].empty())
            Templi::exit("key and label [in keys list] have to be a non-empty string");

        if ((!key["type"].is_array() && !key["type"].is_string()) || key["type"].empty())
            Templi::exit("type [in keys list] must be an array or string and not empty");

        if (key["type"].is_array()) {
            for (auto type : key["type"]) {
                if (!type.is_string())
                    Templi::exit("type items [in keys list] must be a string");
            }
        }

        if (key["type"].is_string()) {
            if (key["type"] != "input" && key["type"] != "bool")
                Templi::exit("type [if string] [in keys list] must be \"input\" or \"bool\"");
        }
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
    
    validate_templi_config(config_json);
    return config_json;
}