#include <Templi/Templi.hpp>

int main(int argc, char const *argv[]){
    Templi::configure("template", "__configured__", {
        "template/main.js",
        "template/all_ignored"
    });

    Templi::generate("__configured__", "__generate__", {
        {"name", "Templi"},
        {"version", "1.0.0"},
        {"date", "2023-01-01"},
        {"Me", "RickaPrincy"},
        {"functionName", "sayHelloWorld"}
    });

    //{{remove}}'value is not given so it will be removed simply 
    return 0;
}