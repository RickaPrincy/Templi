#ifndef __TEMPLI_STRING__
#define __TEMPLI_STRING__

    #include <Templi/types.hpp>
    namespace Templi{
        std::vector<std::pair<String, int>> parseTemplateString(String &text);
        TempliConfig parseConfigString(String &config);
    }

#endif