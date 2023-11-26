#include <Templi/Templi.hpp>

int main(int argc, char const *argv[]){
    Templi::configure("template", "__configured__", {
        "template/main.js"
    });
    return 0;
}