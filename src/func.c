#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAXSTRINGLENGTH 100
#define MAXSTRINGAMOUNT 10
#define MAXCHARWAIT 30
#define MAXSUBSTRINGLENGTH 100
#define SEARCHCHAR *
#define TAGNAMEMAXLENGTH 100
#define SRCMAXLENGTH 100

typedef struct MyString
{
    char *string;
    size_t stringLen;
} MyString;

typedef struct MySubString
{
    int startIndex;
    MyString *string;
    MyString *parentString;
} MySubString;

typedef struct MySrcTreeNode
{
    MySubString data;
    struct MySrcTreeNode *left;
    struct MySrcTreeNode *right;
} MySrcTreeNode;

MySrcTreeNode *newMySrcTreeNode(MySubString data)
{
    // Allocate memory for new MySrcTreeNode
    MySrcTreeNode *temp = (MySrcTreeNode *)malloc(sizeof(MySrcTreeNode));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return (temp);
}

void InsertMySrc(MySubString data, MySrcTreeNode *root)
{
    int cmp = strcmp(data.string->string, root->data.string->string);
    if (root->left != NULL)
        if (cmp > 0)
        {
            if (root->left != NULL)
            {
                InsertMySrc(data, root->left);
            }
            else
            {
                root->left = newMySrcTreeNode(data);
            }
        }
        else if (cmp < 0)
        {
            if (root->right != NULL)
            {
                InsertMySrc(data, root->right);
            }
            else
            {
                root->right = newMySrcTreeNode(data);
            }
        }
        else
        {
            printf("Value is already in the tree!");
        }
}

MyString *allocMyStringMemory(size_t stringLen)
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

MySubString *allocMySubString(size_t parentLen, size_t subLen)
{
    MySubString *temp;
    temp = (MySubString *)malloc(sizeof(MySubString));
    temp->parentString = (MyString *)malloc(sizeof(MyString));
    temp->string = allocMyStringMemory(subLen);
    return temp;
}

bool isAlphaNumerical(char a)
{
    return ((a >= '0' && a <= '9') || (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'));
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

int parseHTMLTag(char *tagText)
{
    return 0;
}

void printLines(MyString **Strings, size_t lineCount)
{
    for (int i = 0; i < lineCount; ++i)
    {
        printf("\n#%i:%s\n length: %li\n", i + 1, Strings[i]->string, Strings[i]->stringLen);
    }
}

size_t readLines(MyString **userInput)
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

size_t getSrcTags(MyString **userInput, size_t linesAmount, char *attrValue, MySrcTreeNode *core)
{
    for (int i = 0; i < linesAmount; ++i)
    {
        MySubString *htmlTag = getSubStringByParams("<", 1, ">", 1, userInput[i]->string, userInput[i]->stringLen);
        printf("HTML TAG FOUND->>>>: \n%s\n", htmlTag->string->string);
        if (htmlTag != NULL)
        {
            size_t spacePlace = findPattern(" ", htmlTag->string->string, htmlTag->string->stringLen, 1, 0);

            if (spacePlace > 1 && spacePlace < 100)
            {
                printStringHighlightByIndex(htmlTag->string->string, htmlTag->string->stringLen, spacePlace);
                printf("spacePlace = %li", spacePlace);
                while (spacePlace > 1)
                {
                    spacePlace--;
                    //printf("\ncheck symbol %c (%li)\n", htmlTag->string->string[spacePlace], spacePlace);
                    if (!(isAlphaNumerical(htmlTag->string->string[spacePlace])))
                    {
                        printf("!!!!!!!!!\n");
                        break;
                    }
                }
                //printf("spacePlace = %li", spacePlace);
                if (spacePlace == 1)
                {
                    MySubString *substr = getSubStringByParams("src=\"", 5, "\"", 1, htmlTag->string->string,
                                                               htmlTag->string->stringLen);
                    printStringHighlightByIndex(substr->string->string, substr->string->stringLen, substr->startIndex);
                }
            }
        }
    }
    return 0;
}

int main()
{
    MyString **userInput = (MyString **)calloc(sizeof(MyString *), MAXSTRINGAMOUNT);
    int linesAmount = readLines(userInput);
    printLines(userInput, linesAmount);
    for (int i = 0; i < linesAmount; ++i)
    {
        getSrcTags(userInput, linesAmount, "anyiguess", NULL);
    }
    /*
    for (int i = 0; i < linesAmount; ++i)
    {
        MySubString *temp = getSubStringByParams("<* ", 3, ">", 1, userInput[i]->string, userInput[i]->stringLen);
        if (temp != NULL)
        {
            printf("\nSTRING FOUND!\n");
            printf("%s\n", temp->string->string);
        }
        else
        {
            //printf("\nSTRING NOT FOUND!\n");
        }
    }*/
    return 0;
}