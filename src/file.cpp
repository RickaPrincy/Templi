#include <Templi/file.hpp>

void Templi::writeLine(std::ofstream *file, std::string text){
    *file << text << "\n";
}

bool Templi::testAndWrite(std::ofstream *file,std::string &text){
    if (file->is_open()) {
        *file << text;
        file->close();
        return true;
    }
    return false;
}

bool Templi::saveOrUpdate(std::string path, std::string &text){
    std::ifstream fileExist(path);
    const bool fileExistStatus = fileExist.good();
    fileExist.close();
    
    if (fileExistStatus) {
        std::ofstream file(path, std::ios::app);
        return testAndWrite(&file, text);
    } else {
        std::ofstream file(path);
        return testAndWrite(&file, text);
    }
}