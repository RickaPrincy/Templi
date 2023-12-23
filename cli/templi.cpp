#include <RCli/RCli.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/Templi.hpp>
#include <Templi/cli.hpp>
#include <TColor/TColor.hpp>

int main(int argc,const char *argv[]){
    Templi::String version = 
        std::to_string(Templi_VERSION_MAJOR) + "." +
        std::to_string(Templi_VERSION_MINOR) + "." +
        std::to_string(Templi_VERSION_PATCH);
    
    RCli::App templi("templi", version, "Generate a project easily");
    templi.add_informations({
        {"Author", "RickaPrincy"},
        {"Github", "<https://github.com/RickaPrincy/Templi"}
    });
    
    Templi::String template_path, output_path;
    Templi::VectorString ignored_paths;
    
    RCli::InputConfig config = RCli::InputConfig().clean(true).required(true);
    RCli::Command configure("configure", "Configure one template to generate templi.json",[&](RCli::Command *_configure){
        Templi::String template_path = _configure->get_option_value("template_path");

        if(template_path.empty()){
            template_path = RCli::ask_input_value(config.text("Path to the template"));
        }
        Templi::configure(template_path);
        TColor::write(TColor::BLUE, "[ DONE ]: ");
        TColor::write(TColor::YELLOW, " templi.json ");
        TColor::write_endl(TColor::BLUE, "was generated for your template");
    });

    configure.add_option(RCli::Option("-t,--template", "Specify template path", "template_path"));
    
    templi.add_subcommand(configure);
    templi.run(argc, argv);
}