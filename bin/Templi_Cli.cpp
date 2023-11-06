#include <Templi/Cli/Templi_Cli.hpp>

using namespace Templi;

int main(int argc, char const *argv[]){
    switch(argc) {
        case 2:
            optionHandler(argv[1]);
            break;
        default:
            writeHelp();
            break;
    }
    return 0;
}
