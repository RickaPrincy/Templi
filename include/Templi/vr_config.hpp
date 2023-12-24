#ifndef __TEMPLI_CONFIG__ 
#define __TEMPLI_CONFIG__ 
    
    #include <Templi/types.hpp> 
    
    namespace Templi{
        json vr_templi_file(String config_path);
        void v_templi_structure(json &config_content);
        MapString vr_templi_keys(json &config_content);
        MapString read_templi_config(String template_path);
    }
#endif