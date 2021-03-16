#include <data/MySubString.h>
#include <stdlib.h>

MySubString *allocMySubString(size_t parentLen, size_t subLen)
{
    MySubString *temp;
    temp = (MySubString *)malloc(sizeof(MySubString));
    temp->parentString = (MyString *)malloc(sizeof(MyString));
    temp->string = (MyString*)allocMyString(subLen);
    return temp;
}


void freeMySubString(MySubString *substr)
{
    free(substr->parentString);
    free(substr->string);
    free(substr);
}