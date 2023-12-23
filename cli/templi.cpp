#include <RCli/RCli.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/Templi.hpp>

int main(int argc,const char *argv[]){
    Templi::String version = 
        std::to_string(RCli_VERSION_MAJOR) + "." +
        std::to_string(RCli_VERSION_MINOR) + "." +
        std::to_string(RCli_VERSION_PATCH);

    RCli::App templi("templi", version, "Generate a project easily");
    
    templi.add_informations({
        {"Author", "RickaPrincy"},
        {"Github", "<https://github.com/RickaPrincy/Templi"}
    });

    templi.run(argc, argv);
}
