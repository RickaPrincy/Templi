#ifndef __TEMPLI_FILE__
#define __TEMPLI_FILE__
    
    #include <string> 
    #include <vector>
    #include <map> 
    #include <fstream>
    #include <tuple>
    #include <Templi/string.hpp>
    
    namespace Templi{
        bool saveFile(std::string path, std::string &text);
        bool deleteFile(std::string path);
        bool writeOpenedFile(std::ofstream *file,std::string &text);

        std::vector<std::string> readFileByLine(std::string path);
        std::vector<std::string> getFolderFiles(std::string path);
        std::vector<Templi::TempliConfig> parseConfigFile(std::string configPath);
    }
#endif