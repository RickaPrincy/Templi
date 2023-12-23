#ifndef __TEMPLI_TYPES__
#define __TEMPLI_TYPES__

    #include <string>
    #include <vector> 
    #include <tuple> 
    #include <map> 
    #include <set> 
    #include <Templi/json.hpp> 
    
    namespace Templi{
        using json = nlohmann::json;
        using String = std::string;
        using VectorString = std::vector<String>;
        using MapString = std::map<String, String>;
        using SetString = std::set<String>;
    } 
 
#endif