#include <Templi/Templi.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    Templi::json myjson = Templi::json::parse("{\"ricka\": {\"name\": }}");
    std::cout << myjson["ricka"] << std::endl;
    return 0;
}