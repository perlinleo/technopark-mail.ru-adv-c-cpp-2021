#include "data/MyString.h"
#include "data/ParsedInfo.h"
#include "parser/parseSRC.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
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
  return 0;
}