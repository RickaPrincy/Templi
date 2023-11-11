#include <gtest/gtest.h>
#include <Templi/string.hpp>
#include <iostream>
#include <tuple>

using TempliWordsConfig = std::vector<std::pair<std::string,int>>;

static void launchTest(std::string &text, Templi::TempliConfig outputs){
    Templi::TempliConfig results = Templi::parseConfigString(text);
    TempliWordsConfig resultWords = std::get<2>(results);
    TempliWordsConfig outputWords = std::get<2>(outputs);

    ASSERT_EQ(std::get<0>(results), std::get<0>(outputs));
    ASSERT_EQ(std::get<1>(results), std::get<1>(outputs));
    ASSERT_EQ(resultWords.size(), outputWords.size());

    if(resultWords.size() == outputWords.size()){
        for(size_t i = 0; i < outputWords.size(); i++){
            ASSERT_EQ(resultWords.at(i).first, outputWords.at(i).first);
            ASSERT_EQ(resultWords.at(i).second, outputWords.at(i).second);
        }
    }
}        

TEST(TempliStringExtractConfig, error_config){
    //Arrange
    Templi::TempliConfig outputs  = { "", -1 , {}};
    std::string text = "dfdfdf/dfdfdfdfdkfdjfk";

    //Act && Assert
    launchTest(text, outputs);
}

TEST(TempliStringExtractConfig, simple_config){
    //Arrange
    std::string text = "hello.txt 5 ricka 5";
    Templi::TempliConfig outputs = {"hello.txt", 5 , {{"ricka", 5}}};

    //Act && Assert
    launchTest(text, outputs);
}

TEST(TempliStringExtractConfig, another_simple_config){
    //Arrange
    std::string text = "main.txt 1 author 6";
    Templi::TempliConfig outputs = { "main.txt",1, {{"author",6}}};

    //Act && Assert
    launchTest(text, outputs);
}