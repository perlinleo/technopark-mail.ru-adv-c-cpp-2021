
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <data/MyString.h>
#define MAXSTRINGAMOUNT 10
#define MAXSTRINGLENGTH 100

MyString *allocMyString(size_t stringLen)
{
    MyString *temp;
    temp = (MyString *)malloc(sizeof(MyString));
    temp->string = (char *)calloc(sizeof(char), stringLen);
    temp->stringLen=stringLen;
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