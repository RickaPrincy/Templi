#include <rcli/rcli.hpp>
#include <TColor/TColor.hpp>
#include "templi/templiConfig.hpp"
#include "templi/templi.hpp"
#include "templi/cli.hpp"

int main(int argc,const char *argv[]){
    templi::String version = 
        std::to_string(templi_VERSION_MAJOR) + "." +
        std::to_string(templi_VERSION_MINOR) + "." +
        std::to_string(templi_VERSION_PATCH);
    
    rcli::App templi("templi", version, "Generate a project easily");
    templi.add_informations({
        {"Author", "RickaPrincy"},
        {"Github", "<https://github.com/RickaPrincy/templi"}
    });
    
    templi::String template_path, output_path;
    templi::VectorString ignored_paths;
    
    rcli::Option template_path_option("-t,--template", "Specify template path", "template_path");
    
    rcli::Command configure("configure", "Configure one template to generate templi.json",[&](rcli::Command *_configure){
        templi::String template_path = _configure->get_option_value("template_path");
        templi::configure_process(template_path);
    });
    configure.add_option(template_path_option);
    
    rcli::Command generate("generate", "Generate new project with one template",[&](rcli::Command *_generate){
        templi::String template_path = _generate->get_option_value("template_path");
        templi::String output_path = _generate->get_option_value("output_path");
        templi::generate_process(template_path, output_path);
    });
    
    generate.add_option(template_path_option);
    generate.add_option(rcli::Option("-o,--output", "Specify output path", "output_path"));

    templi.add_subcommand(configure);
    templi.add_subcommand(generate);

    templi.run(argc, argv);
    return 0;
}