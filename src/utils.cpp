#include <templi/templi.hpp>
#include <RCli/RCli.hpp>
#include <templi/cli.hpp>
#include <templi/cli_utils.hpp>
#include <TColor/TColor.hpp>

void templi::ask_path(templi::String &path, templi::String text){
    if(path.empty()){
        path = RCli::ask_input_value(
            RCli::InputConfig()
                .text(text)
                .required(true)
                .clean(true)
        );
    }
}

void templi::exit(templi::String message){
    TColor::write_endl(TColor::RED, "[ ERROR ]: " + message);
    std::exit(EXIT_FAILURE);
}