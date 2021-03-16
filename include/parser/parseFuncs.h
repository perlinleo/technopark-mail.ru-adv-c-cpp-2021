#ifndef INCLUDE_PARSEFUNCS_PARSEFUNCS_H_
#define INCLUDE_PARSEFUNCS_PARSEFUNCS_H_

#include "include/data/MySubString.h"
#include "include/data/MyString.h"

MySubString *getSubStringByParams(char *startPattern, size_t startPatternLength, char *endPattern,
                                  size_t endPatternLength, char *string, size_t stringLength);

bool isAlphaNumerical(char a);

int findPattern(char *pattern, char *string, size_t stringLength, size_t patternLength, size_t startPoint);

#endif