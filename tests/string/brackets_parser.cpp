#include <gtest/gtest.h>
#include <Templi/parser.hpp>

using namespace Templi;

static void test_result(String &text, String output, MapString values){
    String result = Templi::replace_brackets_words(text, values);
    ASSERT_EQ(result, output);
}

TEST(brakets_parser, no_word){
    //Arrange
    MapString values = {};
    String text = "I have no value";

    //Act && Assert
    test_result(text, text, {});
}

TEST(brakets_parser, one_word){
    //Arrange
    MapString values = {{"one", "cool"}};
    String text = "I have {{one}} value";
    String output = "I have cool value";

    //Act && Assert
    test_result(text, output, values);
}

TEST(brakets_parser, one_word_at_end){
    //Arrange
    MapString values = {{"one", "cool"}};
    String text = "I have {{one}}";
    String output = "I have cool";

    //Act && Assert
    test_result(text, output, values);
}

TEST(brakets_parser, one_word_at_begin){
    //Arrange
    MapString values = {{"je", "cool"}};
    String text = "{{je}} I have";
    String output = "cool I have";

    //Act && Assert
    test_result(text, output, values);
}

TEST(brakets_parser, one_word_only){
    //Arrange
    MapString values = {{"je", "cool"}};
    String text = "{{je}}";
    String output = "cool";

    //Act && Assert
    test_result(text, output, values);
}

TEST(brakets_parser, two_words){
    //Arrange
    MapString values = {{"je", "cool"},{"happy", "noo"}};
    String text = "{{je}} je ricka princy {{happy}} lorem";
    String output = "cool je ricka princy noo lorem";

    //Act && Assert
    test_result(text, output, values);
}

TEST(brakets_parser, many_words){
    //Arrange
    String text = "je{{cool}} I'm happy{{lol}},!no\\ motion {{number1}}, things, {{nice}}";
    String output = "jeje I'm happylolo,!no\\ motion {{number1}}, things, nice";
    MapString values= {
        {"cool", "je"},
        {"lol", "lolo"},
        {"nice", "nice"}
    };

    //Act && Assert
    test_result(text, output, values);
}

TEST(brakets_parser, with_no_close){
    //Arrange
    String text = "je{{cool{{nice}}, {{je";
    String output = "jeVALUE, {{je";
    MapString values = {
        {"cool{{nice", "VALUE"}
    };

    //Act && Assert
    test_result(text, output, values);
}