#ifndef __TEMPLI_STRING__
#define __TEMPLI_STRING__

    #include <string>
    #include <vector>

    namespace Templi{
        std::vector<std::pair<std::string, int>> getWordWithIndex(std::string &text);
    }
#endif