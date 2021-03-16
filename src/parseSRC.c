
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define MAXSTRINGAMOUNT 10
#define MAXSTRINGLENGTH 100

#include <parser/parseFuncs.h>
//#include <include/data/MyResultSrc.h>

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


size_t getSrcTags(MyString **userInput, size_t linesAmount, char *attrValue)
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

//void printSrcTags(MyResultSrc* MyResults, )
