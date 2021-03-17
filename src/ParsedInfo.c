#include <stdio.h>
#include <data/ParsedInfo.h>
#include <stdlib.h>
#include <data/MySubString.h>


ParsedInfo *newParsedInfo(MySubString *HTMLtag , MySubString *srcAttr){
    ParsedInfo* temp = (ParsedInfo*)malloc(sizeof(ParsedInfo));
    temp->HTMLtag = HTMLtag;
    temp->srcAttr = srcAttr;
}

void freeParsedInfo(ParsedInfo *toFree){
    freeMySubString(toFree->HTMLtag);
    freeMySubString(toFree->srcAttr);
    free(toFree);
}

void printParsedInfo(ParsedInfo *ParsedInfo){
    printf("Founded HTML tag\n");
    printMySubString(ParsedInfo->HTMLtag);
    printf("Founded SRC attr\n");
    printMySubString(ParsedInfo->srcAttr);
}


