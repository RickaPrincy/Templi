#ifndef __TEMPLI_CLI__
#define __TEMPLI_CLI__
    
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <initializer_list>
    #include <vector>
    #include <map>
    #include <Templi/file.hpp>

    namespace Templi{
        std::string repeat(std::string text,int number);
        void writeLine(int number = 70);
        void writeKeyValue(std::string key, std::string value);
        void writeKeyValue(std::initializer_list<std::pair<std::string, std::string>> keyValue);
        void writeVersion();
        void writeHelp();
        void writeTitle(std::string title);
        std::string getVersion();       
        void optionHandler(const char*);
        void getInput(std::string text, std::string &value, bool cleanOutput = false, std::string defaultValue = "");
        std::map<std::string, std::string> getAllValues(std::vector<std::string> valuesName, std::string text, bool cleanText = false);
        
        void takeConfiguration();
        void launchConfiguration(std::string config,std::string folderTemplate, std::vector<std::string> &paths);
        void generate();

        template <typename T>
        void saveIterator(std::string path, T &values, std::string separator = ""){
            std::string fileContent = "";
            for(const auto value: values){
                fileContent += value + separator;
            }
            Templi::saveFile(path, fileContent);
        }
    }
#endif
