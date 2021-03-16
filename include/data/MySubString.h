

#ifndef INCLUDE_MYSUBSTRING_MYSUBSTRING_H_
#define INCLUDE_MYSUBSTRING_MYSUBSTRING_H_

#include <stdio.h>
#include <data/MyString.h>

typedef struct MySubString
{
    int startIndex;
    MyString *string;
    MyString *parentString;
} MySubString;

MySubString *allocMySubString(size_t parentLen, size_t subLen);

void freeMySubString(MySubString *substr);
#endif