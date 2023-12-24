#include <Templi/Templi.hpp>
#include <RCli/RCli.hpp>
#include <Templi/cli.hpp>
#include <Templi/cli_utils.hpp>
#include <TColor/TColor.hpp>

void Templi::ask_path(Templi::String &path, Templi::String text){
    if(path.empty()){
        path = RCli::ask_input_value(
            RCli::InputConfig()
                .text(text)
                .required(true)
                .clean(true)
        );
    }
}

void Templi::exit(Templi::String message){
    TColor::write_endl(TColor::RED, "[ ERROR ]: " + message);
    std::exit(EXIT_FAILURE);
}