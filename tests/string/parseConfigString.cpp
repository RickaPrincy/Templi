#include <gtest/gtest.h>
#include <Templi/string.hpp>
#include <iostream>
#include <tuple>

using namespace Templi;

static void launchTest(String &text, TempliConfig outputs){
    TempliConfig results = Templi::parseConfigString(text);
    VectorPairSI resultWords = std::get<2>(results);
    VectorPairSI outputWords = std::get<2>(outputs);

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
    TempliConfig outputs  = { "", -1 , {}};
    String text = "dfdfdf/dfdfdfdfdkfdjfk";

    //Act && Assert
    launchTest(text, outputs);
}

TEST(TempliStringExtractConfig, simple_config){
    //Arrange
    String text = "hello.txt 5 ricka 5";
    TempliConfig outputs = {"hello.txt", 5 , {{"ricka", 5}}};

    //Act && Assert
    launchTest(text, outputs);
}

TEST(TempliStringExtractConfig, another_simple_config){
    //Arrange
    String text = "main.txt 1 author 6";
    TempliConfig outputs = { "main.txt",1, {{"author",6}}};

    //Act && Assert
    launchTest(text, outputs);
}