#include <Templi/Templi.hpp>
#include <Templi/file.hpp>

int main(int argc, char const *argv[]){
    if(argc == 2){
        std::string fileContent = "I'm the best {{name}}";
        Templi::saveFile("main.js", fileContent);
        
        Templi::configure({"main.js"}, "config.templi");
        std::map<std::string, std::string> outptusFiles = {{"main.js", "main.ts"}}, values = { {"name", std::string(argv[1])}};
        Templi::generate("config.templi", values, outptusFiles);
    }
    return 0;
}
