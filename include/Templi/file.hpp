#ifndef __TEMPLI_FILE__
#define __TEMPLI_FILE__
    
    #include <map> 
    #include <fstream>
    #include <Templi/string.hpp>
    
    namespace Templi{
        bool saveFile(String path, String &text);
        bool deleteFile(String path);
        bool writeOpenedFile(std::ofstream *file,String &text);

        VectorString readFileByLine(String path);
        void getFolderFiles(String path,VectorString &result, VectorString excludePath = {});
        VectorConfig parseConfigFile(String configPath);
    }
#endif