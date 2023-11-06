#include <gtest/gtest.h>
#include <Templi/Templi.hpp>
#include <Templi/file.hpp>

int main(int argc, char **argv) {
    std::map<std::string, std::string> values = {
        {"author", "Ricka"},
        {"place", "TANA"},
        {"age", "20"},
        {"ici", "cool"},
    };

    Templi::writeFile("config.txt", values);


    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}