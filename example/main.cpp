#include <Templi/Templi.hpp>

int main(int argc, char const *argv[]){
    Templi::configure("../template", {"../template/all_ingored"});

    Templi::generate("../template", "../generated", {
        {"name", "Templi"},
        {"version", "1.0.0"},
        {"date", "2023-01-01"},
        {"Me", "RickaPrincy"},
        {"functionName", "sayHelloWorld"}
    });

    return 0;
}