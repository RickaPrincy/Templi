#include <gtest/gtest.h>
#include <Templi/Templi.hpp>
#include <Templi/file.hpp>

int main(int argc, char **argv) {
    std::map<std::string, std::string> inputs = {
        {"version", "lol"},
        {"author", "RickaPrincy"}
    };
    
    std::vector<std::tuple<std::string,std::string,int,int>> results;

    results = Templi::extractConfigValue("config.txt", inputs);

    for(const auto result: results){
        std::cout << 
            "file: " << std::get<0>(result) <<
            " word: " << std::get<1>(result) <<
            " line: " << std::get<2>(result) <<
            " column: " << std::get<3>(result) << 
        std::endl;
    }

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}