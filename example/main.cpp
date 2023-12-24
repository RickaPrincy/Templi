#include <Templi/Templi.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    Templi::configure("../template");
    Templi::VectorString my_ignored_files = {"file.txt"};
    
    Templi::generate(
        "../template", 
        "../ctemplate", 
        {{"my_key","my_value"}, {"my_other_key", "my_other_value"}}, 
        my_ignored_files
    );
    return 0;
}