#ifndef __TEMPLI_FILE__
#define __TEMPLI_FILE__
    
    #include <string> 
    #include <vector>
    #include <map> 
    #include <fstream>
    
    namespace Templi{
        void writeLine(std::ofstream *file, std::string text);
        bool saveOrUpdate(std::string path, std::string text);
        bool testAndWrite(std::ofstream *file,std::string text);
    }
#endif