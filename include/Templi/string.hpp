#ifndef __TEMPLI_STRING__
#define __TEMPLI_STRING__

    #include <string>
    #include <vector>
    #include <tuple>

    namespace Templi{
        std::vector<std::pair<std::string, int>> parseTemplateString(std::string &text);
        std::tuple<std::string,std::string,std::string, int, int> parseConfigString(std::string &config);
    }
#endif