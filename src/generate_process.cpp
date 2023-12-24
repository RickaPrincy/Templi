#include <Templi/Templi.hpp>
#include <RCli/RCli.hpp>
#include <Templi/cli.hpp>
#include <Templi/cli_utils.hpp>
#include <Templi/exception.hpp>
#include <Templi/vr_config.hpp>
#include <TColor/TColor.hpp>

void Templi::generate_process(Templi::String template_path, Templi::String output_path){
    Templi::ask_path(template_path, "Path to the template");
    Templi::ask_path(output_path, "Path to the output");
    
    Templi::json config_content = read_templi_config(template_path);
    
    Templi::MapString values = Templi::vr_templi_keys(config_content);
    Templi::VectorString ignored_paths = Templi::vr_templi_ignored_paths(config_content);

    Templi::generate(template_path, output_path, values, ignored_paths);
}