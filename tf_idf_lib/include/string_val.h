// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#ifndef INCLUDE_STRING_VAL_H_
#define INCLUDE_STRING_VAL_H_

#include <stdio.h>

typedef struct string_val {
  char* key;
  float val;
} string_val;

void sort_string_val_array(string_val**, size_t counter);

void print_top_5(string_val** strings_from_doc, size_t counter);

#endif  // INCLUDE_STRING_VAL_H_