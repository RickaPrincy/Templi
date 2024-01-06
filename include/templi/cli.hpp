#ifndef __TEMPLI_CLI_FUNCTION__
#define __TEMPLI_CLI_FUNCTION__

    #include <templi/types.hpp> 
    #include <RCli/RCli.hpp> 

    namespace templi{
        void configure_process(String template_path);
        void generate_process(String template_path, String output_path);
    }
#endif