#ifndef INCLUDE_DATA_MYSUBSTRING_H_
#define INCLUDE_DATA_MYSUBSTRING_H_

#include <data/MyString.h>
#include <stdio.h>

typedef struct MySubString {
  int startIndex;
  MyString *string;
  MyString *parentString;
} MySubString;

MySubString *allocMySubString(size_t parentLen, size_t subLen);

void freeMySubString(MySubString *substr);

void printMySubString(MySubString *substr);
#endif  // INCLUDE_DATA_MYSUBSTRING_H_
