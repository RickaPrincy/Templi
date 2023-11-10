#include <gtest/gtest.h>
#include <Templi/string.hpp>
#include <iostream>

using TempliResult = std::vector<std::pair<std::string, int>>;

static void testResults(std::string &text, TempliResult outputs){
    TempliResult results = Templi::parseTemplateString(text);

    ASSERT_EQ(results.size(),outputs.size());
    if(results.size() != outputs.size())
        return;

    for(size_t i = 0; i < results.size(); i++){
        ASSERT_EQ(results.at(i).first, outputs.at(i).first);
        ASSERT_EQ(results.at(i).second, outputs.at(i).second);
    }
}

TEST(TempliStringGetPosition, no_word){
    //Arrange
    TempliResult outputs = {};
    std::string text = "I have no value";

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("I have no value", text);
}

TEST(TempliStringGetPosition, one_word){
    //Arrange 
    std::string text = "I'mone test for{{you}} so tell me";
    TempliResult outputs = {{"you",15}};

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("I'mone test for so tell me", text);
}

TEST(TempliStringGetPosition, one_word_at_end){
    //Arrange
    std::string text = "mone{{name}}";
    TempliResult outputs = {{"name", 4}};

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("mone", text);
}

TEST(TempliStringGetPosition, one_word_at_begin){
    //Arrange
    std::string text = "{{cool}}test";
    TempliResult outputs = {{"cool", 0}};
    
    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("test", text);
}

TEST(TempliStringGetPosition, one_word_only){
    //Arrange
    std::string text = "{{cool}}";
    TempliResult outputs = {{"cool", 0}};

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("", text);
}

TEST(TempliStringGetPosition, two_words){
    //Arrange
    std::string text = "{{cool}}I'm happy{{lol}}";
    TempliResult outputs = {
        {"cool", 0},
        {"lol", 9}
    };

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("I'm happy", text);
}

TEST(TempliStringGetPosition, many_words){
    //Arrange
    std::string text = "je{{cool}}I'm happy{{lol}},!no\\ motion{{number1}}, things, {{nice}}";
    TempliResult outputs = {
        {"cool", 2},
        {"lol", 11},
        {"number1", 23},
        {"nice", 33}
    };

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("jeI'm happy,!no\\ motion, things, ", text);
}

TEST(TempliStringGetPosition, with_no_close){
    //Arrange
    std::string text = "je{{cool{{nice}}, {{je";
    TempliResult outputs = {
        {"cool{{nice", 2}
    };

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("je, {{je", text);
}