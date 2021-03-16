#include <include/data/MySubString.h>

MySubString *allocMySubString(size_t parentLen, size_t subLen)
{
    MySubString *temp;
    temp = (MySubString *)malloc(sizeof(MySubString));
    temp->parentString = (MyString *)malloc(sizeof(MyString));
    temp->string = allocMyStringMemory(subLen);
    return temp;
}

MySubString *getSubStringByParams(char *startPattern, size_t startPatternLength, char *endPattern,
                                  size_t endPatternLength, char *string, size_t stringLength)
{
    int start, end,
        i = 0;
    start = findPattern(startPattern, string, stringLength, startPatternLength, 0);
    if (start == -1)
        return (void *)0;
    printf("checking from %i char \n", start);
    end = findPattern(endPattern, string, stringLength, endPatternLength, start + startPatternLength);
    if (end == -1)
        return (void *)0;
    printStringHighlightByIndex(string, stringLength, start);
    printStringHighlightByIndex(string, stringLength, end);
    //printf("\nstart: %i \nend: %i \n", start, end);
    if (start < end)
    {
        MySubString *temp = allocMySubString(stringLength, end - start + endPatternLength);
        temp->startIndex = start;
        for (i = 0; i < end - start + endPatternLength; ++i)
        {
            //printf("\n_(%i)_\n", i + start);
            temp->string->string[i] = string[i + start];
            //printf("||%i %c == %c||\n", i, substr.subStringText[i], string[i + start]);
        }
        temp->string->stringLen = i;
        //substr.subStringText[end - start + 1] = '\0';
        return temp;
    }
    return (void *)0;
}

void freeMySubString(MySubString *substr)
{
    free(substr->parentString);
    free(substr->string);
    free(substr);
}