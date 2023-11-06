#include <gtest/gtest.h>
#include <Templi/string.hpp>
#include <iostream>
#include <tuple>

using TempliExtracted = std::tuple<std::string,std::string,std::string,int,int>;

static void testResults(std::string &text, TempliExtracted outputs){
    TempliExtracted results = Templi::extractValues(text);

    ASSERT_EQ(std::get<0>(results), std::get<0>(outputs));
    ASSERT_EQ(std::get<1>(results), std::get<1>(outputs));
    ASSERT_EQ(std::get<2>(results), std::get<2>(outputs));
    ASSERT_EQ(std::get<3>(results), std::get<3>(outputs));
    ASSERT_EQ(std::get<4>(results), std::get<4>(outputs));
}

TEST(TempliStringExtractConfig, error_config){
    //Arrange
    TempliExtracted outputs = { "", "","", -1, -1};
    std::string text = "dfdfdf/dfdfdfdfdkfdjfk";

    //Act && Assert
    testResults(text, outputs);
}

TEST(TempliStringExtractConfig, simple_config){
    //Arrange
    TempliExtracted outputs = { "hello.txt","hello.txt.output","ricka", 5, 6};
    std::string text = "hello.txt/hello.txt.output/ricka/5/6";

    //Act && Assert
    testResults(text, outputs);
}

TEST(TempliStringExtractConfig, another_simple_config){
    //Arrange
    TempliExtracted outputs = { "main.txt","main.txt.output","author", 1, 6};
    std::string text = "main.txt/main.txt.output/author/1/6";

    //Act && Assert
    testResults(text, outputs);
}