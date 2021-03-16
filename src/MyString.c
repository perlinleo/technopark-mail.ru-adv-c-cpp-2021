
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <include/data/MyString.h>
#define MAXSTRINGAMOUNT 10
#define MAXSTRINGLENGTH 100

MyString *allocMyString(size_t stringLen)
{
    MyString *temp;
    temp = (MyString *)malloc(sizeof(MyString));
    temp->string = (char *)calloc(sizeof(char), stringLen);
    return temp;
}

void freeString(MyString *string)
{
    free(string->string);
    free(string);
}

void printMyStrings(MyString **Strings, size_t lineCount)
{
    for (int i = 0; i < lineCount; ++i)
    {
        printf("\n#%i:%s\n length: %li\n", i + 1, Strings[i]->string, Strings[i]->stringLen);
    }
}

int findPattern(char *pattern, char *string, size_t stringLength, size_t patternLength, size_t startPoint)
{
    int patternCounter = 0,
        startIndex = 0,
        j = 0,
        k = 0;
    bool paternFound = false;
    for (int i = startPoint; i < stringLength; i++)
    {
        if (j == patternLength)
            return startIndex;
        if (string[i] == pattern[0])
        {
            startIndex = i;
            for (j = 1; j < patternLength; j++)
            {
                i++;
                //printf("char %c = %c\n", string[i], pattern[j]);
                if (string[i] != pattern[j])
                {
                    i -= j;
                    break;
                }
            }
        }
    }
    if (j == patternLength)
        return startIndex;
    else
        return -1;
}

void printStringHighlightByIndex(char *string, size_t stringLength, size_t highlightIndex)
{
    assert(highlightIndex < 100);

    printf("\n%s\n", string);
    for (int i = 0; i < highlightIndex; ++i)
    {
        printf("~");
    }
    printf("^\n");
}

size_t readMyStrings(MyString **userInput)
{
    size_t i = 0;
    char inputBuff[100];
    char ch;
    size_t read;
    fprintf(stdout, "PRESS CTRL+D TO SKIP STRING AND STOP...\n");
    for (i; i < MAXSTRINGAMOUNT; ++i)
    {
        fprintf(stdout, "String %li:", i + 1);
        for (read = 0; read < MAXSTRINGLENGTH && (ch = getc(stdin)) != '\n';)
        {
            inputBuff[read] = ch;
            ++read;
        }
        //100 extra chars read?!?!?!??!
        if (inputBuff[read - 1] != EOF)
        {
            userInput[i] = (MyString *)malloc(sizeof(MyString));
            userInput[i]->string = (char *)calloc(sizeof(char), read);
            memcpy(userInput[i]->string, inputBuff, read);
            userInput[i]->stringLen = read;
        }
        else
        {
            fprintf(stdout, "(((STOPPED)))");
            return i;
        }
    }
    return i;
}