#ifndef __TEMPLI_STRING__
#define __TEMPLI_STRING__

    #include <string>
    #include <vector>
    #include <tuple>

    namespace Templi{
        using TempliConfig = std::tuple<std::string, int, std::vector<std::pair<std::string, int>>>;
        std::vector<std::pair<std::string, int>> parseTemplateString(std::string &text);
        TempliConfig parseConfigString(std::string &config);
    }
#endif