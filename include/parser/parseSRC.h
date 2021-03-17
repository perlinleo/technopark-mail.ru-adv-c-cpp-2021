
#ifndef INCLUDE_PARSER_PARSESRC_H_
#define INCLUDE_PARSER_PARSESRC_H_

#include <data/MyString.h>
#include <data/ParsedInfo.h>
#include <stdio.h>

size_t getSrcTags(MyString **userInput, size_t linesAmount, char *attrValue,
                  ParsedInfo **result);

#endif