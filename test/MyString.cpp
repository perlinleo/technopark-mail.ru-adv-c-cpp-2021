#include "gtest/gtest.h"

extern "C" {
#include "data/MyString.h"
#include <string.h>
}

void checkMem(MyString* string){
  char S = string->string[0];
}

TEST(allocMyString, correct) {
  MyString *test = allocMyString(11);
  char *str = (char *)malloc(sizeof(char) * 11);
  for (int i = 0; i < 11; ++i) {
    str[i] = 'a';
  }
  test->string = str;
  ASSERT_EQ(11, test->stringLen);
  ASSERT_EQ(str, test->string);
}

TEST(freeString, check){
  MyString *testString = allocMyString(5);
  testString->string = (char*)malloc(sizeof(char)*5);
  testString->stringLen = 5;
  ASSERT_EXIT((checkMem(testString),exit(0)),::testing::ExitedWithCode(0),".*");
  freeString(testString);
  //обращение после FREE
  ASSERT_EXIT((checkMem(testString),exit(0)),::testing::KilledBySignal(SIGSEGV),".*");
}

/*
TEST(readTest, correctInput){
  MyString **userInput =
      (MyString **)calloc(sizeof(MyString *), 4);
  system("ECHO 'hello1\nhello2\nhello3\nhello4\n'");
  size_t linesAmount = readMyStrings(userInput);
  printMyStrings(userInput, linesAmount);
}
*/