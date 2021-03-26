// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <hashtable.h>

int main(int argc, char **argv) {
  char string[50];
  hashtable_t *ht = create_hash_table();
  while (1) {
    scanf("%49s", string);
    add_value(ht, string);
    print_hash_table(ht);
    printf("word hello was found %i times\n",
           counter_for_word_ex_ht(ht, "hello"));
  }
  printf("%d\n", create_hash("hello"));
  return 0;
}
