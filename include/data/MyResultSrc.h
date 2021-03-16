#ifndef INCLUDE_MYSTRING_MYRESULTSRC_H_
#define INCLUDE_MYSTRING_MYRESULTSRC_H_

#include <stdio.h>
#include <data/MySubString.h>

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