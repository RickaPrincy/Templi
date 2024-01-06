#ifndef __TEMPLI_TEMPLATE__
#define __TEMPLI_TEMPLATE__

    #include <fstream>
    #include <templi/types.hpp>    

    namespace templi{
        void generate(String template_path,String output_path, MapString values, VectorString ignored_path = {});
        void configure(String template_path, VectorString ignored_path={});
    }

#endif