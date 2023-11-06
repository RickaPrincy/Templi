#include <Templi/file.hpp>
#include <Templi/string.hpp>

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

std::vector<std::tuple<std::string, std::string, int, int>> Templi::extractConfigValue(std::string configPath, std::map<std::string, std::string> &values){
    std::vector<std::tuple<std::string, std::string, int, int>> extraced;
    std::ifstream configFile(configPath);
    std::string lineContent, lastFileName = "";
    int line{1}, lastLine{-1}, sameFileSameLine{1};

    if(!configFile.is_open())
        extraced;
    
    while(std::getline(configFile, lineContent)){
        std::tuple<std::string, std::string, int, int> value = Templi::extractValues(lineContent);
        const std::string fileNameValue = std::get<0>(value), wordValue = std::get<1>(value);
        size_t lineValue = std::get<2>(value), indexValue = std::get<3>(value);

        if(fileNameValue != "" && values.find(wordValue) != values.end()){
            const std::string wordContent = values.at(wordValue);
            if( lastFileName == fileNameValue && lastLine == lineValue){
                indexValue += wordContent.size() * sameFileSameLine;
                sameFileSameLine++;
            }else{
                sameFileSameLine = 1;
            }

            extraced.push_back(std::make_tuple(fileNameValue,wordContent, lineValue, indexValue));
            lastFileName = fileNameValue;
            lastLine = lineValue;
        }
    }
    configFile.close();
    
    return extraced;
}