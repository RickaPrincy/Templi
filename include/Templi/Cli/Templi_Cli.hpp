#ifndef __TEMPLI_CLI__
#define __TEMPLI_CLI__
    
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <initializer_list>
    #include <vector>
    #include <map>

    namespace Templi{
        std::string repeat(std::string text,int number);
        void writeLine(int number = 70);
        void writeKeyValue(std::string key, std::string value);
        void writeKeyValue(std::initializer_list<std::pair<std::string, std::string>> keyValue);
        void writeVersion();
        void writeHelp();
        void writeTitle(std::string title);
        std::string getVersion();       
        void optionHandler(const char*);

        void configure();
    }
#endif
