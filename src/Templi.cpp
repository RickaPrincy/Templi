#include <iostream>
#include <Templi/Templi.hpp>

bool Templi::configureFile(std::string path, std::string configPath){
    std::ifstream fileExist(path);
    const bool fileExistStatus = fileExist.good();
    fileExist.close();
    
    if (fileExistStatus) {
        std::ofstream file(path, std::ios::app);
        
        if (file.is_open()) {

            file.close();
        } else {
            return false;
        }
    } else {
        std::ofstream file(path);
        if (file.is_open()) {

            file.close();
        } else {
            return false;
        }
    }
    return false;
}