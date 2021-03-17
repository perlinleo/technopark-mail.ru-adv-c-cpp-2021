#include "gtest/gtest.h"

extern "C" {
#include "data/MyString.h"
#include <string.h>
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
