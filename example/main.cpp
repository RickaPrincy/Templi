#include <Templi/file.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    Templi::findPosition("../template/hello.txt", "helo");
    return 0;
}