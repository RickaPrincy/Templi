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
        void getFolderFiles(String path, VectorString &result, VectorString excludePath = {});
        bool copyFolder(String source, String destination);
        VectorConfig parseConfigFile(String configPath);
        
        template <typename T>
        void saveIterator(String path, T &values, String separator = ""){
            String fileContent = "";
            for(const auto value: values){
                fileContent += value + separator;
            }
            saveFile(path, fileContent);
        }

        void writeConfigContent(String templateFolder, String configuredPath,VectorConfig &configs);
    }
#endif