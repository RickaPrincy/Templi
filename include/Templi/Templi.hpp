#ifndef __TEMPLI_TEMPLATE__
#define __TEMPLI_TEMPLATE__

    #include <string>
    #include <fstream>
    #include <map>
    #include <set>
    
    namespace Templi{
        std::set<std::string> configureFile(std::string path,std::string outputPath, std::string configPath);
        bool writeFile(std::string configPath, std::map<std::string, std::string> values);
    }

#endif