#include <Templi/Templi.hpp>
#include <RCli/RCli.hpp>
#include <Templi/cli.hpp>
#include <Templi/cli_utils.hpp>
#include <Templi/exception.hpp>
#include <Templi/config.hpp>
#include <TColor/TColor.hpp>

void Templi::generate_process(Templi::String template_path, Templi::String output_path){
    Templi::ask_path(template_path, "Path to the template");
    Templi::ask_path(output_path, "Path to the output");
    Templi::VectorString keys_types = { "bool", "input" };
}