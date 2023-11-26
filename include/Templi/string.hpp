#ifndef __TEMPLI_STRING__
#define __TEMPLI_STRING__

    #include <Templi/types.hpp>
    namespace Templi{
        VectorPairSI parseTemplateString(String &text);
        TempliConfig parseConfigString(String &config);
    }

#endif