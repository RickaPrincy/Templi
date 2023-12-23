#ifndef __TEMPLI_CONFIG__ 
#define __TEMPLI_CONFIG__ 
    
    #include <Templi/types.hpp> 
    
    namespace Templi{
        void valid_templi_config(json &config_content);
        json read_templi_config(String template_path);
    }
#endif