// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <string_val.h>

void sort_string_val_array(string_val** strings_from_doc, size_t counter) {
  string_val* temp;
  for (int i = counter - 2; i >= 0; i--) {
    for (int j = 0; j <= i; j++) {
      if (strings_from_doc[j]->val < strings_from_doc[j + 1]->val) {
        temp = strings_from_doc[j];
        strings_from_doc[j] = strings_from_doc[j + 1];
        strings_from_doc[j + 1] = temp;
      }
    }
  }
  printf("_________________________\n");
}

void print_top_5(string_val** strings_from_doc) {
  for (int i = 0; i < 5; ++i) {
    printf(strings_from_doc[i]->key);
    printf("%f", strings_from_doc[i]->val);
    printf("\n");
  }
}
