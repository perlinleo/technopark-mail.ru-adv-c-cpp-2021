#ifndef INCLUDE_PARSER_PARSEFUNCS_H_
#define INCLUDE_PARSER_PARSEFUNCS_H_

#include "data/MyString.h"
#include "data/MySubString.h"

MySubString *getSubStringByParams(char *startPattern, size_t startPatternLength,
                                  char *endPattern, size_t endPatternLength,
                                  char *string, size_t stringLength);

bool isAlphaNumerical(char a);

int findPattern(char *pattern, char *string, size_t stringLength,
                size_t patternLength, size_t startPoint);

#endif  // INCLUDE_PARSER_PARSEFUNCS_H_