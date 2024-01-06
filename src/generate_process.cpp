#include <rcli/rcli.hpp>
#include <TColor/TColor.hpp>
#include "templi/templi.hpp"
#include "templi/cli.hpp"
#include "templi/cli_utils.hpp"
#include "templi/vr_config.hpp"

void templi::generate_process(templi::String template_path, templi::String output_path){
    templi::ask_path(template_path, "Path to the template");
    templi::ask_path(output_path, "Path to the output");
    
    templi::json config_content = read_templi_config(template_path);
    
    templi::MapString values = templi::vr_templi_keys(config_content);
    templi::VectorString ignored_paths = templi::vr_templi_ignored_paths(config_content);

    templi::generate(template_path, output_path, values, ignored_paths);
}