#include <gtest/gtest.h>
#include <Templi/string.hpp>
#include <iostream>

using namespace Templi;

static void testResults(String &text, VectorPairSI outputs){
    VectorPairSI results = Templi::parseTemplateString(text);

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
    VectorPairSI outputs = {};
    String text = "I have no value";

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("I have no value", text);
}

TEST(TempliStringGetPosition, one_word){
    //Arrange 
    String text = "I'mone test for{{you}} so tell me";
    VectorPairSI outputs = {{"you",15}};

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("I'mone test for so tell me", text);
}

TEST(TempliStringGetPosition, one_word_at_end){
    //Arrange
    String text = "mone{{name}}";
    VectorPairSI outputs = {{"name", 4}};

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("mone", text);
}

TEST(TempliStringGetPosition, one_word_at_begin){
    //Arrange
    String text = "{{cool}}test";
    VectorPairSI outputs = {{"cool", 0}};
    
    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("test", text);
}

TEST(TempliStringGetPosition, one_word_only){
    //Arrange
    String text = "{{cool}}";
    VectorPairSI outputs = {{"cool", 0}};

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("", text);
}

TEST(TempliStringGetPosition, two_words){
    //Arrange
    String text = "{{cool}}I'm happy{{lol}}";
    VectorPairSI outputs = {
        {"cool", 0},
        {"lol", 9}
    };

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("I'm happy", text);
}

TEST(TempliStringGetPosition, many_words){
    //Arrange
    String text = "je{{cool}}I'm happy{{lol}},!no\\ motion{{number1}}, things, {{nice}}";
    VectorPairSI outputs = {
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
    String text = "je{{cool{{nice}}, {{je";
    VectorPairSI outputs = {
        {"cool{{nice", 2}
    };

    //Act && Assert
    testResults(text, outputs);
    ASSERT_EQ("je, {{je", text);
}