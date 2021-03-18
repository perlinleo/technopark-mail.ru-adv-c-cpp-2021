#ifndef INCLUDE_MYSTRING_MYRESULTSRC_H_
#define INCLUDE_MYSTRING_MYRESULTSRC_H_

#include <data/MySubString.h>
#include <stdio.h>

#define MAXPARSEDINFOAMOUNT 100

typedef struct ParsedInfo {
  MySubString *HTMLtag;
  MySubString *srcAttr;
} ParsedInfo;

ParsedInfo *newParsedInfo(MySubString *HTMLtag, MySubString *srcAttr);
void freeParsedInfo(ParsedInfo *toFree);
void printParsedInfo(ParsedInfo *ParsedInfo);

#endif  // INCLUDE_DATA_PARSEDINFO_H_