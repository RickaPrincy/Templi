#ifndef __TEMPLI_TEMPLATE__
#define __TEMPLI_TEMPLATE__

    #include <fstream>
    #include <Templi/types.hpp>    

    namespace Templi{
        SetString configure(VectorString paths, String configPath);
        void generate(String configPath, MapString values, MapString outputs);
    }

#endif