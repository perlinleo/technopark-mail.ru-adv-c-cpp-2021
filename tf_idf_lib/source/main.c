// Copyright 2021 Leonid Vadimovich Perlin perlinleo@gmail.com.
// All rights reserved.

#include <hashtable.h>
#include <read_data.h>

int main(int argc, char **argv) {
  /*char string[50];
  hashtable_t *ht = create_hash_table();
  while (1) {
    scanf("%49s", string);
    add_value(ht, string);
    print_hash_table(ht);
    printf("word hello was found %i times\n",
           counter_for_word_ex_ht(ht, "hello"));
  }
  printf("%d\n", create_hash("hello"));
  */

  system("pwd");
  hashtable_t * hashtable= create_hash_table();
  fill_hashtable_from_file("../data/1.txt",hashtable);
  print_hash_table(hashtable);
  
  return 0;
}
