#ifndef __TEMPLI_TEMPLATE__
#define __TEMPLI_TEMPLATE__

    #include <string>
    #include <fstream>
    #include <map>
    #include <set>
    #include <vector>
    
    namespace Templi{
        std::set<std::string> configure(std::vector<std::string> paths, std::string configPath);
        void generate(std::string configPath, std::map<std::string, std::string> values, std::map<std::string, std::string> outputs);
    }

#endif