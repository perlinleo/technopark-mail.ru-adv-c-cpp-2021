#include "gtest/gtest.h"

extern "C" {
#include "data/MySubString.h"
#include "data/MyString.h"
#include <string.h>
}

void checkMem(MySubString* test){
    char a1 = test->parentString->string[0];
}

TEST (freeMySubString, correct){
    MyString *testParent = allocMyString(10);
    testParent->string = "1234567890";
    testParent->stringLen = 10;
    MyString *testString = allocMyString(5);
    testString->string = "45678";
    testString->stringLen = 5;
    MySubString* test = allocMySubString(10,5);
    test->parentString = testParent;
    test->string = testString;
    test->startIndex = 4;
    
    // первый случай -> обращение по памяти возможно
    ASSERT_EXIT((checkMem(test),exit(0)),::testing::ExitedWithCode(0),".*");
    freeMySubString(test);
    
    // второй случай -> обращение к памяти после FREE
    ASSERT_EXIT((checkMem(test),exit(0)),::testing::KilledBySignal(SIGSEGV),".*");
}
