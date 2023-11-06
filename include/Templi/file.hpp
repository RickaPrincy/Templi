#ifndef __TEMPLI_FILE__
#define __TEMPLI_FILE__
    
    #include <string> 
    #include <vector>
    #include <map> 
    
    namespace Templi{
        bool fileExists(std::string path);
        std::vector<std::map<std::string,std::pair<int, int>>> findPosition(std::string filePath, std::string word);
    }
#endif