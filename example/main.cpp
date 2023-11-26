#include <Templi/Templi.hpp>

int main(int argc, char const *argv[]){
    Templi::configure("__template__", "__configured__", {
        "__template__/main.js",
        "__template__/all_ignored"
    });

    Templi::generate("__configured__", "__generated__", {
        {"name", "Templi"},
        {"version", "1.0.0"},
        {"date", "2023-01-01"},
        {"Me", "RickaPrincy"},
        {"functionName", "sayHelloWorld"}
    });

    //{{remove}}'value is not given so it will be removed simply 
    return 0;
}