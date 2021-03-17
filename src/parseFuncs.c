#include <stdbool.h>
#include <stdlib.h>

#include "data/MySubString.h"

bool isAlphaNumerical(char a) {
  return ((a >= '0' && a <= '9') || (a >= 'A' && a <= 'Z') ||
          (a >= 'a' && a <= 'z'));
}

int findPattern(char *pattern, char *string, size_t stringLength,
                size_t patternLength, size_t startPoint) {
  int patternCounter = 0, startIndex = 0, j = 0;
  for (int i = startPoint; i < stringLength; i++) {
    if (j == patternLength)
      return startIndex;
    if (string[i] == pattern[0]) {
      startIndex = i;
      for (j = 1; j < patternLength; j++) {
        i++;
        // printf("char %c = %c\n", string[i], pattern[j]);
        if (string[i] != pattern[j]) {
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

MySubString *getSubStringByParams(char *startPattern, size_t startPatternLength,
                                  char *endPattern, size_t endPatternLength,
                                  char *string, size_t stringLength) {
  int start, end;

  start =
      findPattern(startPattern, string, stringLength, startPatternLength, 0);
  if (start == -1)
    return (void *)0;
  // printf("checking from %i char \n", start);
  end = findPattern(endPattern, string, stringLength, endPatternLength,
                    start + startPatternLength);
  if (end == -1)
    return (void *)0;
  // printStringHighlightByIndex(string, stringLength, start);
  // printStringHighlightByIndex(string, stringLength, end);
  // printf("\nstart: %i \nend: %i \n", start, end);
  if (start < end) {
    int i = 0;
    MySubString *temp =
        allocMySubString(stringLength, end - start + endPatternLength);
    temp->startIndex = start;
    for (i; i < end - start + endPatternLength; ++i) {
      // printf("\n_(%i)_\n", i + start);
      temp->string->string[i] = string[i + start];
      // printf("||%i %c == %c||\n", i, substr.subStringText[i], string[i +
      // start]);
    }
    temp->string->stringLen = i;
    // substr.subStringText[end - start + 1] = '\0';
    temp->parentString->string = (char *)malloc(sizeof(char) * stringLength);
    temp->parentString->stringLen = stringLength;
    return temp;
  }
  return (void *)0;
}
