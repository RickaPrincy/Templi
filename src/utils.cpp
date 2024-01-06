#include <rcli/rcli.hpp>
#include <TColor/TColor.hpp>
#include "templi/templi.hpp"
#include "templi/cli.hpp"
#include "templi/cli_utils.hpp"

void templi::ask_path(templi::String &path, templi::String text){
    if(path.empty()){
        path = rcli::ask_input_value(
            rcli::InputConfig()
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