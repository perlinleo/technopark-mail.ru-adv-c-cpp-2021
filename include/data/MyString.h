#ifndef INCLUDE_MYSTRING_MYSTRING_H_
#define INCLUDE_MYSTRING_MYSTRING_H_

#include <stdio.h>
#define MAXSTRINGAMOUNT 10

typedef struct MyString
{
    char *string;
    size_t stringLen;
} MyString;

MyString *allocMyString(size_t stringLen);

void freeString(MyString *string);

void printMyStrings(MyString **Strings, size_t lineCount);

size_t readMyStrings(MyString **userInput);

#endif