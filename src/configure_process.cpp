#include <rcli/rcli.hpp>
#include <TColor/TColor.hpp>
#include "templi/templi.hpp"
#include "templi/cli.hpp"
#include "templi/cli_utils.hpp"

void templi::configure_process(templi::String template_path){
    templi::ask_path(template_path, "Path to the template");
    templi::configure(template_path);
    TColor::write(TColor::BLUE, "[ DONE ]: ");
    TColor::write(TColor::YELLOW, "templi.json ");
    TColor::write_endl(TColor::BLUE, "was generated for your template");
}