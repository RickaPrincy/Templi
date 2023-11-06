#include <gtest/gtest.h>
#include <Templi/file.hpp>
#include <iostream>
#include <tuple>

using TempliConfigExtracted = std::vector<std::tuple<std::string,std::string, std::string, int ,int>>;

static void launchTest(std::string configContent,std::map<std::string, std::string> &values, TempliConfigExtracted &outputs){
    Templi::deleteFile("templi_test_config.templi");
    Templi::saveOrUpdate("templi_test_config.templi", configContent);

    TempliConfigExtracted results = Templi::extractConfigValue("templi_test_config.templi", values);

    ASSERT_EQ(results.size(),outputs.size());

    if(results.size() != outputs.size())
        return;

    for(size_t i = 0; i < results.size(); i++){
        const auto result = results.at(i);
        const auto output = outputs.at(i);

        ASSERT_EQ(std::get<0>(result), std::get<0>(output));
        ASSERT_EQ(std::get<1>(result), std::get<1>(output));
        ASSERT_EQ(std::get<2>(result), std::get<2>(output));
        ASSERT_EQ(std::get<3>(result), std::get<3>(output));
        ASSERT_EQ(std::get<4>(result), std::get<4>(output));
    }

    Templi::deleteFile("templi_test_config.templi");
}

TEST(TempliFileExtractConfig, no_match){
    //Arrange
    std::string config = "hello.txt/hello.txt.output/author/5/ricka\nmain.cpp/version/\n,main.cpp/version/55///5\n";
    std::map<std::string, std::string> values = {};
    TempliConfigExtracted outputs = {};
    
    //Act && Assert
    launchTest(config, values, outputs);
}

TEST(TempliFileExtractConfig, one_match_but_no_values){
    //Arrange
    std::string config = "hello.txt/hello.txt.output/author/5/ricka\nmain.cpp/main.cpp.output/version/5/8\n,main.cpp/version/55///5\n";
    std::map<std::string, std::string> values = {};
    TempliConfigExtracted outputs = {};
    
    //Act && Assert
    launchTest(config, values, outputs);
}

TEST(TempliFileExtractConfig, one_match){
    //Arrange
    std::string config = "hello.txt/output/author/5/ricka\nmain.cpp/output.txt/version/5/8\n,main.cpp/version/55///5\n";
    std::map<std::string, std::string> values = {{"version", "1.0.0"}};
    TempliConfigExtracted outputs = {{"main.cpp","output.txt","1.0.0",5,8}};
    
    //Act && Assert
    launchTest(config, values, outputs);
}

TEST(TempliFileExtractConfig, two_match){
    //Arrange
    std::string config = "hello.txt/output.txt/author/5/8\nmain.cpp/output.txt/version/8/10\n,main.cpp/version/55///5\n";
    std::map<std::string, std::string> values = {
        {"version", "1.0.0"},
        {"author", "RickaPrincy"}
    };
    TempliConfigExtracted outputs = {
        {"hello.txt","output.txt","RickaPrincy",5,8},
        {"main.cpp","output.txt","1.0.0",8,10},
    };
    
    //Act && Assert
    launchTest(config, values, outputs);
}