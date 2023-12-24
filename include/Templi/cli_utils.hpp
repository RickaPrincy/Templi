#ifndef __TEMPLI_CLI_UTILS__
#define __TEMPLI_CLI_UTILS__

    #include <Templi/types.hpp> 
    #include <RCli/RCli.hpp> 
    
    namespace Templi{
        void ask_path(String &path, String text);
        void exit(String message);
    }

#endif