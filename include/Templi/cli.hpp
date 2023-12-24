#ifndef __TEMPLI_CLI_FUNCTION__
#define __TEMPLI_CLI_FUNCTION__

    #include <Templi/types.hpp> 
    #include <RCli/RCli.hpp> 

    namespace Templi{
        void configure_process(String template_path);
        void generate_process(String template_path, String output_path);
    }
#endif