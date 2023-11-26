#ifndef __TEMPLI_TEMPLATE__
#define __TEMPLI_TEMPLATE__

    #include <fstream>
    #include <Templi/types.hpp>    

    namespace Templi{
        SetString configure(String templateFolder, String configuredPath, VectorString ignoredPaths = {});
        void generate(String configuredPath,String outputFolder, MapString values);
    }

#endif