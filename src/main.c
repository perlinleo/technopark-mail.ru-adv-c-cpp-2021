#include "include/data/MyString.h"
#include "include/parser/parseSRC.h"
#include <stdio.h>

int main()
{
    MyString **userInput = (MyString **)calloc(sizeof(MyString *), MAXSTRINGAMOUNT);
    int linesAmount = readLines(userInput);
    printLines(userInput, linesAmount);
    for (int i = 0; i < linesAmount; ++i)
    {
        getSrcTags(userInput, linesAmount, "anyiguess");
    }
    return 0;
}