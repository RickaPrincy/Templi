#include <Templi/Templi.hpp>
#include <RCli/RCli.hpp>
#include <Templi/cli.hpp>
#include <Templi/cli_utils.hpp>
#include <TColor/TColor.hpp>

void Templi::configure_process(Templi::String template_path){
    Templi::ask_path(template_path, "Path to the template");
    Templi::configure(template_path);
    TColor::write(TColor::BLUE, "[ DONE ]: ");
    TColor::write(TColor::YELLOW, " templi.json ");
    TColor::write_endl(TColor::BLUE, "was generated for your template");
}