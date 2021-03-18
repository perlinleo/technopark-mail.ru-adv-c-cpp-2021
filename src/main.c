#include "data/MyString.h"
#include "data/ParsedInfo.h"
#include "parser/parseSRC.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  /*
  MyString **userInput =
      (MyString **)calloc(sizeof(MyString *), MAXSTRINGAMOUNT);
  size_t linesAmount = readMyStrings(userInput);
  printMyStrings(userInput, linesAmount);
  ParsedInfo **result =
      (ParsedInfo **)calloc(sizeof(ParsedInfo *), MAXPARSEDINFOAMOUNT);
  size_t filteredAmount =
      getSrcTags(userInput, linesAmount, "anyiguess??", result);

  for (int i = 0; i < filteredAmount; ++i) {
    printParsedInfo(result[i]);
  }
  for (int i = 0; i < MAXPARSEDINFOAMOUNT; ++i) {
    freeParsedInfo(result[i]);
  }
  free(result);
  */
  MyString **userInput =
      (MyString **)calloc(sizeof(MyString *), 1);
    size_t linesAmount = 1;
    userInput[0]=allocMyString(30);
    userInput[0]->string="saddasda<htmltag src=\"check\" >";
    userInput[0]->stringLen=30;
    ParsedInfo **result =(ParsedInfo **)calloc(sizeof(ParsedInfo *), 1);
    size_t filteredAmount = getSrcTags(userInput, linesAmount, 
    "anyiguess??", result);
    //ASSERT_EQ(filteredAmount,1);
    // printParsedInfo(result[0]);
  return 0;
}