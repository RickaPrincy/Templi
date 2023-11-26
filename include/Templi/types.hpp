#ifndef __TEMPLI_TYPES__
#define  __TEMPLI_TYPES__

    #include <string>
    #include <vector> 
    #include <tuple> 
    #include <map> 
    #include <set> 
    
    namespace Templi{
        using String = std::string;
        using TempliConfig = std::tuple<String, int, std::vector<std::pair<String, int>>>;
        using VectorString = std::vector<String>;
        using MapString = std::map<String, String>;
        using SetString = std::set<String>;
        using VectorPairSI = std::vector<std::pair<std::string, int>>;
        using VectorConfig = std::vector<TempliConfig>;
    } 
 
#endif