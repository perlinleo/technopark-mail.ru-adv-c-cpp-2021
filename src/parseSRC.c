
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRINGAMOUNT 10
#define MAXSTRINGLENGTH 100

#include <data/ParsedInfo.h>
#include <parser/parseFuncs.h>


size_t getSrcTags(MyString **userInput, size_t linesAmount, char *attrValue,
                  ParsedInfo **result) {
  size_t counter = 0;
  for (int i = 0; i < linesAmount; ++i) {
    MySubString *htmlTag = getSubStringByParams(
        "<", 1, ">", 1, userInput[i]->string, userInput[i]->stringLen);

    if (htmlTag != NULL) {
      // HTML TAG FOUND
      size_t spacePlace = findPattern(" ", htmlTag->string->string,
                                      htmlTag->string->stringLen, 1, 0);

      if (spacePlace > 1 && spacePlace < 100) {
        // printStringHighlightByIndex(htmlTag->string->string,
        // htmlTag->string->stringLen, spacePlace); printf("spacePlace = %li",
        // spacePlace);
        while (spacePlace > 1) {
          spacePlace--;
          // printf("\ncheck symbol %c (%li)\n",
          // htmlTag->string->string[spacePlace], spacePlace);
          if (!(isAlphaNumerical(htmlTag->string->string[spacePlace]))) {
            //<hellosrc check>
            break;
          }
        }
        // printf("spacePlace = %li", spacePlace);
        if (spacePlace == 1) {
          MySubString *substr = getSubStringByParams(
              "src=\"", 5, "\"", 1, htmlTag->string->string,
              htmlTag->string->stringLen);
          if (substr != NULL) {
            printf("\n%s\n%s", htmlTag->string->string, substr->string->string);
            result[counter] = newParsedInfo(htmlTag, substr);
            counter++;
          }
        }
      }
    }
  }
  return counter;
}

// void printSrcTags(MyResultSrc* MyResults, )
