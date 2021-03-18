#include "gtest/gtest.h"

extern "C" {
#include "data/MyString.h"
#include "data/ParsedInfo.h"
#include "parser/parseSRC.h"
}

TEST(getSrcTags, htmlTagNoAttr){
    MyString **userInput =
      (MyString **)calloc(sizeof(MyString *), 1);
    size_t linesAmount = 1;
    userInput[0]=allocMyString(24);
    userInput[0]->string="<html tagwithoutsrcattr>";
    userInput[0]->stringLen=24;
    ParsedInfo **result =(ParsedInfo **)calloc(sizeof(ParsedInfo *), 1);
    size_t filteredAmount = getSrcTags(userInput, linesAmount, 
    "anyiguess??", result);
    ASSERT_EQ(filteredAmount,0);
}

TEST(getSrcTags, nohtmlTagNoAttr){
    MyString **userInput =
      (MyString **)calloc(sizeof(MyString *), 1);
    size_t linesAmount = 1;
    userInput[0]=allocMyString(23);
    userInput[0]->string="nohtmltaginagivenstring";
    userInput[0]->stringLen=23;
    ParsedInfo **result =(ParsedInfo **)calloc(sizeof(ParsedInfo *), 1);
    size_t filteredAmount = getSrcTags(userInput, linesAmount, 
    "anyiguess??", result);
    ASSERT_EQ(filteredAmount,0);
}

TEST(getSrcTags, correct){
    MyString **userInput =
      (MyString **)calloc(sizeof(MyString *), 1);
    size_t linesAmount = 1;
    userInput[0]=allocMyString(30);
    userInput[0]->string="saddasda<htmltag src=\"check\" >";
    userInput[0]->stringLen=30;
    ParsedInfo **result =(ParsedInfo **)calloc(sizeof(ParsedInfo *), 1);
    size_t filteredAmount = getSrcTags(userInput, linesAmount, 
    "anyiguess??", result);
    const char* htmlTest="<htmltag src=\"check\" >";
    for(int i=0;i<22;++i){
      ASSERT_EQ(htmlTest[i],result[0]->HTMLtag->string->string[i]);
    }
    // ASSERT_EQ("<htmltag src=\"check\" >",&(result[0]->HTMLtag->string->string));
    const char* attrTest="src=\"check\"";
    for(int i=0;i<11;++i){
      ASSERT_EQ(attrTest[i],result[0]->srcAttr->string->string[i]);
    }
    ASSERT_EQ(filteredAmount,1);
}

TEST(getSrcTags, wrongHTMLtag){
    MyString **userInput =
      (MyString **)calloc(sizeof(MyString *), 1);
    size_t linesAmount = 1;
    userInput[0]=allocMyString(24);
    userInput[0]->string="<dsdss\"***sda tagwithoutsrcattr>";
    userInput[0]->stringLen=24;
    ParsedInfo **result =(ParsedInfo **)calloc(sizeof(ParsedInfo *), 1);
    size_t filteredAmount = getSrcTags(userInput, linesAmount, 
    "anyiguess??", result);
    ASSERT_EQ(filteredAmount,0);
}



