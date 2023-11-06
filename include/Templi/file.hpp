#ifndef __TEMPLI_FILE__
#define __TEMPLI_FILE__
    
    #include <string> 
    #include <vector>
    #include <map> 
    #include <fstream>
    #include <tuple>
    
    namespace Templi{
        void writeLine(std::ofstream *file, std::string text);
        bool saveOrUpdate(std::string path, std::string &text);
        bool deleteFile(std::string path);
        bool testAndWrite(std::ofstream *file,std::string &text);
        std::vector<std::tuple<std::string, std::string,std::string, int, int>> extractConfigValue(std::string configPath, std::map<std::string, std::string> &values);
    }
#endif