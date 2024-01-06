#include <templi/templi.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    templi::configure("../template");
    templi::VectorString my_ignored_files = {"file.txt"};
    
    templi::generate(
        "../template", 
        "../ctemplate", 
        {{"my_key","my_value"}, {"my_other_key", "my_other_value"}}, 
        my_ignored_files
    );
    return 0;
}