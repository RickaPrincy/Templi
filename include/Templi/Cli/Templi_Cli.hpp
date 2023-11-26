#ifndef __TEMPLI_CLI__
#define __TEMPLI_CLI__
    
    #include <iostream>
    #include <fstream>
    #include <initializer_list>
    #include <Templi/file.hpp>

    namespace Templi{
        String repeat(String text,int number);
        void writeLine(int number = 70);
        void writeKeyValue(String key, String value);
        void writeKeyValue(std::initializer_list<std::pair<String, String>> keyValue);
        void writeVersion();
        void writeHelp();
        void writeTitle(String title);
        String getVersion();       
        void optionHandler(const char*);
        void getInput(String text, String &value, bool cleanOutput = false, String defaultValue = "");
        MapString getAllValues(VectorString valuesName, String text, bool cleanText = false);
        
        void takeConfiguration();
        void launchConfiguration(String config,String folderTemplate, VectorString &paths);
        void generate();

    }
#endif
