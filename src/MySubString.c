#include <data/MySubString.h>
#include <stdlib.h>

void printStringHighlightByIndex(char *string, size_t stringLength,
                                 size_t highlightIndex) {
  printf("\n%s\n", string);
  for (int i = 0; i < highlightIndex; ++i) {
    printf("~");
  }
  printf("^\n");
}

MySubString *allocMySubString(size_t parentLen, size_t subLen) {
  MySubString *temp;
  temp = (MySubString *)malloc(sizeof(MySubString));
  temp->parentString = (MyString *)malloc(sizeof(MyString));
  temp->string = (MyString *)allocMyString(subLen);
  return temp;
}

void printMySubString(MySubString *substr) {
  printStringHighlightByIndex(substr->parentString->string,
                              substr->parentString->stringLen,
                              substr->startIndex);
}

void freeMySubString(MySubString *substr) {
  free(substr->parentString);
  free(substr->string);
  free(substr);
}