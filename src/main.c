#include "data/MyString.h"
#include "parser/parseSRC.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    MyString **userInput = (MyString **)calloc(sizeof(MyString *), MAXSTRINGAMOUNT);
    int linesAmount = readMyStrings(userInput);
    printMyStrings(userInput, linesAmount);
    for (int i = 0; i < linesAmount; ++i)
    {
        getSrcTags(userInput, linesAmount, "anyiguess");
    }
    return 0;
}